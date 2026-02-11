GetOutputWordTypeSize(int dataType)
{
#ifdef VTK_USE_64BIT_IDS


  if((dataType == VTK_ID_TYPE) && (this->IdType == vtkXMLWriter::Int32))
    {
    return 4;
    }
#endif
  return this->GetWordTypeSize(dataType);
}
