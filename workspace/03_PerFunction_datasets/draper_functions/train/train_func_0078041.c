processCallMacro(xmlNode *localroot)
{
  string const n = (const char *) localroot->properties->children->content;
  int npar = 0;

  xmlNode *macro = macro_map[macros[n]];

  for(xmlAttr *i = macro->properties; i != NULL; i = i->next)
  {
    if(!xmlStrcmp(i->name, (const xmlChar *) "npar"))
    {
      npar = atoi((const char *) i->children->content);
      break;
    }
  }

  TransferWord **myword = NULL;
  if(npar > 0)
  {
    myword = new TransferWord *[npar];
  }
  string **myblank = NULL;
  if(npar > 1)
  {
    myblank = new string *[npar - 1];
  }

  int idx = 0;
  int lastpos = 0;
  for(xmlNode *i = localroot->children; i != NULL; i = i->next)
  {
    if(i->type == XML_ELEMENT_NODE)
    {
      int pos = atoi((const char *) i->properties->children->content)-1;
      myword[idx] = word[pos];
      if(idx-1 >= 0)
      {
        myblank[idx-1] = blank[lastpos];
      }
      idx++;
      lastpos = pos;
    }
  }

  swap(myword, word);
  swap(myblank, blank);
  swap(npar, lword);

  for(xmlNode *i = macro->children; i != NULL; i = i->next)
  {
    if(i->type == XML_ELEMENT_NODE)
    {
      processInstruction(i);
    }
  }

  swap(myword, word);
  swap(myblank, blank);
  swap(npar, lword);

  if(myword)
  {
    delete myword;
  }
  if(myblank)
  {
    delete myblank;
  }
}
