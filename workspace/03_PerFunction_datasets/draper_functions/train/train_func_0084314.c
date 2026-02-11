InternalUpdate()
{

  if (this->Input)
    {
    if (this->Concatenation->GetInverseFlag())
      {
      this->Input->GetInverse()->Update();
      }
    else
      {
      this->Input->Update();
      }
    }


  int nTransforms = this->Concatenation->GetNumberOfTransforms();
  for (int i = 0; i < nTransforms; i++)
    {
    this->Concatenation->GetTransform(i)->Update();
    }
}
