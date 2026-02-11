Write()
{
  ConstTransformListType &transformList =
    this->GetWriteTransformList();

  std::ofstream        out;
  this->OpenStream(out, false);

  out << "#Insight Transform File V1.0" << std::endl;

  const std::string CompositeTransformTypeName =
    transformList.front()->GetTransformTypeAsString();


  CompositeTransformIOHelper helper;
  if(CompositeTransformTypeName.find("CompositeTransform") != std::string::npos)
    {
    transformList = helper.GetTransformList(transformList.front().GetPointer());
    }
  vnl_vector< double > TempArray;
  int count = 0;

  ConstTransformListType::const_iterator end = transformList.end();

  for (ConstTransformListType::const_iterator it = transformList.begin();
       it != end; ++it,++count )
    {
    const std::string TransformTypeName = ( *it )->GetTransformTypeAsString();
    out << "#Transform " << count << std::endl;
    out << "Transform: " << ( *it )->GetTransformTypeAsString() << std::endl;


    if(TransformTypeName.find("CompositeTransform") != std::string::npos)
      {
      if(count > 0)
        {
        itkExceptionMacro(<< "Composite Transform can only be 1st transform in a file");
        }
      }
    else
      {
      TempArray = ( *it )->GetParameters();
      out << "Parameters: ";
      print_vector(out,TempArray);
      out << std::endl;
      TempArray = ( *it )->GetFixedParameters();
      out << "FixedParameters: ";
      print_vector(out,TempArray);
      out << std::endl;
      }
    }
  out.close();
}
