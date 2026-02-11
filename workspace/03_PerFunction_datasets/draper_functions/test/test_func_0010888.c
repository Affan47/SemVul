vtkDelimitedTextWriterGetDataString(
  vtkArrayIteratorTemplate<vtkStdString>* iter, vtkIdType tupleIndex,
  ostream* stream, vtkDelimitedTextWriter* writer, bool* first)
{
  int numComps = iter->GetNumberOfComponents();
  vtkIdType index = tupleIndex* numComps;
  for (int cc=0; cc < numComps; cc++)
    {
    if ((index+cc) < iter->GetNumberOfValues())
      {
      if (*first == false)
        {
        (*stream) << writer->GetFieldDelimiter();
        }
      *first = false;
      (*stream) << writer->GetString(iter->GetValue(index+cc));
      }
    else
      {
      if (*first == false)
        {
        (*stream) << writer->GetFieldDelimiter();
        }
      *first = false;
      }
    }
}
