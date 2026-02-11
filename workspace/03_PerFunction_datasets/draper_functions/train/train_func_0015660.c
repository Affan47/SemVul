vtkXMLStructuredDataReaderSubExtentCopyValues(
  vtkArrayIteratorTemplate<vtkStdString>* destIter, vtkIdType destIndex,
  vtkArrayIteratorTemplate<vtkStdString>* srcIter, vtkIdType srcIndex,
  vtkIdType numValues)
{
  vtkIdType maxIndex = destIndex + numValues;
  for (vtkIdType cc=destIndex; cc < maxIndex; ++cc)
    {
    destIter->GetValue(cc) =
      srcIter->GetValue(srcIndex++);
    }
}
