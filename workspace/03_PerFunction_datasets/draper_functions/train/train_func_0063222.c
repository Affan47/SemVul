createMacro(wstring const &name, int const value)
{
  if(td.getMacros().find(name) != td.getMacros().end())
  {
    parseError(L"Macro '" + name + L"' defined at least twice");
  }
  td.getMacros()[name] = value;
}
