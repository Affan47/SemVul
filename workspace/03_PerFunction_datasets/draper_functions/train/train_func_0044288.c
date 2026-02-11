___SCMOBJ_to_in_addr
   ___P((___SCMOBJ addr,
         struct in_addr *ia,
         int arg_num),
        (addr,
         ia,
         arg_num)
___SCMOBJ addr;
struct in_addr *ia;
int arg_num;)
{
  if (addr == ___FAL)
    ia->s_addr = htonl (INADDR_ANY);
  else
    ia->s_addr = htonl ((___INT(___U8VECTORREF(addr,___FIX(0)))<<24) +
                        (___INT(___U8VECTORREF(addr,___FIX(1)))<<16) +
                        (___INT(___U8VECTORREF(addr,___FIX(2)))<<8) +
                        ___INT(___U8VECTORREF(addr,___FIX(3))));

  return ___FIX(___NO_ERR);
}
