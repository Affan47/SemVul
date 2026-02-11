CanWriteFile(const char *name)
{
  std::string filename = name;

  if ( filename == "" )
    {
    itkDebugMacro(<< "No filename specified.");
    }

  bool extensionFound = CheckExtension(name);

  if ( !extensionFound )
    {
    itkDebugMacro(<< "The filename extension is not recognized");
    return false;
    }

  if ( extensionFound )
    {
    return true;
    }
  return false;
}
