InitializeLookupTables(vtkVolume *vol)
{
  this->Superclass::InitializeLookupTables(vol);


  glGenTextures(1, reinterpret_cast<GLuint *>(&this->TransferFunctionTexture));
  glBindTexture(GL_TEXTURE_1D, this->TransferFunctionTexture);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, vtkgl::CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA8, this->TransferFunctionSize,0,
               GL_RGBA,GL_FLOAT, this->TransferFunction);

  if (!this->PsiTableTexture)
    {
    vtkUnstructuredGridPartialPreIntegration *ppi =
      vtkUnstructuredGridPartialPreIntegration::New();
    ppi->BuildPsiTable();
    int tableSize = 0;
    float *psiTable = ppi->GetPsiTable(tableSize);


    glGenTextures(1, reinterpret_cast<GLuint *>(&this->PsiTableTexture));
    glBindTexture(GL_TEXTURE_2D, this->PsiTableTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, vtkgl::CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, vtkgl::CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE8, tableSize, tableSize,
                 0, GL_LUMINANCE, GL_FLOAT, psiTable);
    ppi->Delete();
    }
}
