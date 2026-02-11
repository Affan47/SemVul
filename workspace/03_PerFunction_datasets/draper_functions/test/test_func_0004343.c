ToUnicode(istream& InputStream)
{

  vtkUnicodeString returnString;

  vtkUnicodeStringOutputIterator StringIterator(returnString);
  this->ToUnicode(InputStream, StringIterator);

  return returnString;
}
