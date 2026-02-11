PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "Name: " << (this->GetName()? this->GetName() : "(none)")
                                                                    << endl;
  os << indent << "Scope: ";
  switch(this->GetScope())
    {
  case SCOPE_NONE:
    os << "None";
    break;
  case SCOPE_MIXED:
    os << "Mixed";
    break;
  case SCOPE_VERTEX:
    os << "Vertex";
    break;
  case SCOPE_FRAGMENT:
    os << "Fragment";
    break;
    }
  os << endl;

  os << indent << "Language: ";
  switch (this->GetLanguage())
    {
  case LANGUAGE_NONE:
    os << "None";
    break;
  case LANGUAGE_MIXED:
    os << "Mixed";
    break;
  case LANGUAGE_CG:
    os << "Cg";
    break;
  case LANGUAGE_GLSL:
    os << "GLSL";
    }
  os << endl;

  os << indent << "Location: ";
  switch (this->GetLocation())
    {
  case LOCATION_NONE:
    os << "None";
    break;
  case LOCATION_INLINE:
    os << "Inline";
    break;
  case LOCATION_FILE:
    os << "(loaded from a source file)";
    break;
  case LOCATION_LIBRARY:
    os << "Library";
    break;
    }
  os << endl;

  os << indent << "Entry: "
    <<  (this->GetEntry()? this->GetEntry() : "(none)") << endl;
  os << indent << "Args: ";
  const char** args = this->GetArgs();
  if (!args)
    {
    os << "(none)" << endl;
    }
  else
    {
    while (*args)
      {
      os << indent << *args << " ";
      args++;
      }
    os << endl;
    }

  os << indent << "RootElement: ";
  if (this->RootElement)
    {
    os << endl;
    this->RootElement->PrintSelf(os, indent.GetNextIndent());
    }
  else
    {
    os << "(none)" << endl;
    }
}
