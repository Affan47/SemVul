HandleXMLChild(const wxChar *tag)
{
   if (wxStrcmp(tag, wxT("controlpoint")))
      return NULL;

   return AddPointAtEnd(0,0);
}
