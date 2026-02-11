PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "EnabledArray: ";
  if( this->EnabledArray )
    {
    this->EnabledArray->PrintSelf(os << "\n", indent.GetNextIndent());
    }
  else
    {

    os << "(none)\n";
    }
}
