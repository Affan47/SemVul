clr_varlist_bool(DLLIST * varlist)
{
   DLNODE *nd = varlist->first;
   BOOL ok = TRUE;

   while (nd && ok)
   {
      HSCATTR *attr = (HSCATTR *) nd->data;

      if ((attr->vartype == VT_BOOL) && !(attr->text))
         set_varbool(attr, FALSE);

      nd = nd->next;
   }
}
