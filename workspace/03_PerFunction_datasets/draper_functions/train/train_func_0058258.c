___in6_addr_to_SCMOBJ
   ___P((struct in6_addr *ia,
         int arg_num),
        (ia,
         arg_num)
struct in6_addr *ia;
int arg_num;)
{
  int i;
  ___SCMOBJ result;

  for (i=0; i<16; i++)
    if (ia->s6_addr[i] != 0)
      break;

  if (i == 16)
    result = ___FAL;
  else
    {
      result = ___alloc_scmobj (___sU16VECTOR, 8<<1, ___STILL);

      if (___FIXNUMP(result))
        return ___FIX(___CTOS_HEAP_OVERFLOW_ERR+arg_num);

      for (i=0; i<8; i++)
        ___U16VECTORSET
          (result,
           ___FIX(i),
           ___FIX((___CAST(___U16,ia->s6_addr[i<<1])<<8) +
                  ia->s6_addr[(i<<1)+1]))
    }

  return result;
}
