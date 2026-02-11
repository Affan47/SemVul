___find_symkey_from_scheme_string
   ___P((___SCMOBJ str,
         unsigned int subtype),
        (str,
         subtype)
___SCMOBJ str;
unsigned int subtype;)
{
  ___SCMOBJ tbl;
  ___SCMOBJ probe;
  ___SCMOBJ h = hash_scheme_string (str);

  tbl = symkey_table (subtype);
  probe = ___FIELD(tbl, ___INT(h) % (___INT(___VECTORLENGTH(tbl))-1) + 1);

  while (probe != ___NUL)
    {
      ___SCMOBJ name = ___FIELD(probe,___SYMKEY_NAME);
      long i = 0;
      long n = ___INT(___STRINGLENGTH(name));
      if (___INT(___STRINGLENGTH(str)) == n)
        {
          for (i=0; i<n; i++)
            if (___STRINGREF(str,___FIX(i)) != ___STRINGREF(name,___FIX(i)))
              goto next;
          return probe;
        }
    next:
      probe = ___FIELD(probe,___SYMKEY_NEXT);
    }

  return ___FAL;
}
