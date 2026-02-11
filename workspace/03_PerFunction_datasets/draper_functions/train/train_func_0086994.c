commutative(void    (*oper) ())
{
   return oper == ob_add || oper == os_mult
      || oper == ob_eq || oper == ob_ne
      || oper == ob_and || oper == ob_xor || oper == ob_or;
}
