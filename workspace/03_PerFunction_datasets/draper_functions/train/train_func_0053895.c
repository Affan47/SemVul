procDefVars()
{
  while(type != XML_READER_TYPE_END_ELEMENT ||
	name != L"section-def-vars")
  {
    step();
    if(name == L"def-var")
    {
      if(type != XML_READER_TYPE_END_ELEMENT)
      {
        createVar(attrib(L"n"), attrib(L"v"));
      }
    }
    else if(name == L"#text")
    {

    }
    else if(name == L"#comment")
    {

    }
    else if(name == L"section-def-vars")
    {

    }
    else
    {
      parseError(L"Unexpected '<" + name + L">' tag");
    }
  }
}
