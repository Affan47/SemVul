ScalarTypeCallback()
{
  if (!this->GetInput())
    {
    return "unsigned char";
    }

  switch (this->GetInput()->GetScalarType())
    {
    case VTK_DOUBLE:
      { return "double"; }
    case VTK_FLOAT:
      { return "float"; }
    case VTK_LONG:
      { return "long"; }
    case VTK_UNSIGNED_LONG:
      { return "unsigned long"; }
    case VTK_INT:
      { return "int"; }
    case VTK_UNSIGNED_INT:
      { return "unsigned int"; }
    case VTK_SHORT:
      { return "short"; }
    case VTK_UNSIGNED_SHORT:
      { return "unsigned short"; }
    case VTK_CHAR:
      { return "char"; }
    case VTK_UNSIGNED_CHAR:
      { return "unsigned char"; }
    case VTK_SIGNED_CHAR:
      { return "signed char"; }
    default:
      { return "<unsupported>"; }
    }
}
