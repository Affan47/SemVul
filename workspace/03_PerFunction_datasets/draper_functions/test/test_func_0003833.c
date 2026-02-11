procDefAttrs()
{
  wstring attrname = L"";

  while(type != XML_READER_TYPE_END_ELEMENT ||
	name != L"section-def-attrs")
  {
    step();
    if(name == L"attr-item")
    {
      if(type != XML_READER_TYPE_END_ELEMENT)
      {
        insertAttrItem(attrname, attrib(L"tags"));
      }
    }
    else if(name == L"def-attr")
    {
      if(type != XML_READER_TYPE_END_ELEMENT)
      {
        attrname = attrib(L"n");
      }
      else
      {
        wstring all = td.getAttrItems()[attrname];
        td.getAttrItems()[attrname] = L"(" + all + L")";
        attrname = L"";
      }
    }
    else if(name == L"#text")
    {

    }
    else if(name == L"#comment")
    {

    }
    else if(name == L"section-def-attrs")
    {

    }
    else
    {
      parseError(L"Unexpected '<" + name + L">' tag");
    }
  }
}
