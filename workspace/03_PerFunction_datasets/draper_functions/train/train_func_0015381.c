cons(struct stemmer * z, int i)
{  switch (z->b[i])
   {  case 'a': case 'e': case 'i': case 'o': case 'u': return FALSE;
      case 'y': return (i == 0) ? TRUE : !cons(z, i - 1);
      default: return TRUE;
   }
}
