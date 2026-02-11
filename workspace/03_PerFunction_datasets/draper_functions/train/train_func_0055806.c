addNode(GList **lst, OpenBabel::OBAtom *atom)
{
  char *ele;
  GList *tmplst;
  GList *lstatom;
  gboolean found;

  ele = getSymbol(atom);


  found = FALSE;
  tmplst = *lst;
  while (tmplst && !found)
    {
      lstatom = (GList*)tmplst->data;
      if ( !strcmp(getSymbol((OpenBabel::OBAtom*)lstatom->data), ele) )
	{

	  lstatom = g_list_prepend(lstatom, (gpointer)atom);
	  tmplst->data = lstatom;
	  found = TRUE;
	}
      tmplst = g_list_next(tmplst);
    }
  if (!found)
    {

      lstatom = (GList*)0;
      lstatom = g_list_prepend(lstatom, (gpointer)atom);
      *lst = g_list_prepend(*lst, lstatom);
    }
}
