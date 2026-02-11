WriteData()
{

  this->StartFile();
  vtkIndent indent = vtkIndent().GetNextIndent();


  ostream& os = *(this->Stream);

  if (this->Internal->Root)
    {
    this->Internal->Root->PrintXML(os, indent);
    }

  return this->EndFile();
}
