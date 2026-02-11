PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
  os << indent << "Renderer: ";
  if (this->Renderer)
    {
    os << "\n";
    this->Renderer->PrintSelf(os, indent.GetNextIndent());
    }
  else
    {
    os << "(none)";
    }
  os << indent << "ScreenSize: " << this->ScreenSize << endl;
  os << indent << "Scaling: " << (this->Scaling ? "on" : "off") << endl;
}
