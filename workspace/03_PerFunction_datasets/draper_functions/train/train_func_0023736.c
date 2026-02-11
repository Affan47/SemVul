DestroyXMLParser()
{
  if(!this->XMLParser)
    {
    vtkErrorMacro("DestroyXMLParser() called with no current XMLParser.");
    return;
    }
  this->XMLParser->Delete();
  this->XMLParser = 0;
}
