___for_each_symkey
   ___P((unsigned int subtype,
         void (*visit) (___SCMOBJ symkey, void *data),
         void *data),
        (subtype,
         visit,
         data)
unsigned int subtype;
void (*visit) ();
void *data;)
{
  ___SCMOBJ tbl = symkey_table (subtype);
  int i;

  for (i=___INT(___VECTORLENGTH(tbl))-1; i>0; i--)
    {
      ___SCMOBJ probe = ___FIELD(tbl, i);

      while (probe != ___NUL)
        {
          visit (probe, data);
          probe = ___FIELD(probe,___SYMKEY_NEXT);
        }
    }
}
