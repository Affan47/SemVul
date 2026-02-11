vtkWrap_GetTypeName(ValueInfo *val)
{
  unsigned int aType = val->Type;
  const char *aClass = val->Class;


  switch (aType & VTK_PARSE_BASE_TYPE)
    {
    case VTK_PARSE_FLOAT:          return "float";
    case VTK_PARSE_DOUBLE:         return "double";
    case VTK_PARSE_INT:            return "int";
    case VTK_PARSE_SHORT:          return "short";
    case VTK_PARSE_LONG:           return "long";
    case VTK_PARSE_VOID:           return "void ";
    case VTK_PARSE_CHAR:           return "char";
    case VTK_PARSE_UNSIGNED_INT:   return "unsigned int";
    case VTK_PARSE_UNSIGNED_SHORT: return "unsigned short";
    case VTK_PARSE_UNSIGNED_LONG:  return "unsigned long";
    case VTK_PARSE_UNSIGNED_CHAR:  return "unsigned char";
    case VTK_PARSE_ID_TYPE:        return "vtkIdType";
    case VTK_PARSE_LONG_LONG:      return "long long";
    case VTK_PARSE___INT64:        return "__int64";
    case VTK_PARSE_UNSIGNED_LONG_LONG: return "unsigned long long";
    case VTK_PARSE_UNSIGNED___INT64:   return "unsigned __int64";
    case VTK_PARSE_SIGNED_CHAR:    return "signed char";
    case VTK_PARSE_BOOL:           return "bool";
    case VTK_PARSE_UNICODE_STRING: return "vtkUnicodeString";
    case VTK_PARSE_SSIZE_T:        return "ssize_t";
    case VTK_PARSE_SIZE_T:         return "size_t";
    }

  return aClass;
}
