Read()
{
  std::ifstream matfile(this->GetFileName(),
                        std::ios::in | std::ios::binary);

  if ( matfile.fail() )
    {
    matfile.close();
    itkExceptionMacro("The file could not be opened for read access "
                      << std::endl << "Filename: \"" << this->GetFileName() << "\"");
    }
  while ( !matfile.eof() )
    {
    vnl_matlab_readhdr mathdr(matfile);
    if ( !mathdr )
      {
      break;
      }
    if ( mathdr.cols() != 1 )
      {
      matfile.close();
      itkExceptionMacro
        ("Only vector parameters supported");
      }
    TransformType::ParametersType TmpParameterArray( mathdr.rows() );
    ReadMat(mathdr, TmpParameterArray);
    std::string classname( mathdr.name() );

    TransformPointer transform;
    this->CreateTransform(transform, classname);
    this->GetReadTransformList().push_back(transform);
    vnl_matlab_readhdr mathdr2(matfile);
    if ( mathdr2.cols() != 1 )
      {
      matfile.close();
      itkExceptionMacro
        ("Only vector parameters supported");
      }
    TransformType::ParametersType TmpFixedParameterArray( mathdr2.rows() );
    ReadMat(mathdr2, TmpFixedParameterArray);
    transform->SetFixedParameters(TmpFixedParameterArray);
    transform->SetParametersByValue(TmpParameterArray);
    }
  matfile.close();
}
