is_anchored(register const pcre_uchar *code, unsigned int bracket_map,
  unsigned int backref_map)
{
do {
   const pcre_uchar *scode = first_significant_code(
     code + PRIV(OP_lengths)[*code], FALSE);
   register int op = *scode;


   if (op == OP_BRA  || op == OP_BRAPOS ||
       op == OP_SBRA || op == OP_SBRAPOS)
     {
     if (!is_anchored(scode, bracket_map, backref_map)) return FALSE;
     }


   else if (op == OP_CBRA  || op == OP_CBRAPOS ||
            op == OP_SCBRA || op == OP_SCBRAPOS)
     {
     int n = GET2(scode, 1+LINK_SIZE);
     int new_map = bracket_map | ((n < 32)? (1 << n) : 1);
     if (!is_anchored(scode, new_map, backref_map)) return FALSE;
     }


   else if (op == OP_ASSERT || op == OP_ONCE || op == OP_ONCE_NC ||
            op == OP_COND)
     {
     if (!is_anchored(scode, bracket_map, backref_map)) return FALSE;
     }


   else if ((op == OP_TYPESTAR || op == OP_TYPEMINSTAR ||
             op == OP_TYPEPOSSTAR))
     {
     if (scode[1] != OP_ALLANY || (bracket_map & backref_map) != 0)
       return FALSE;
     }


   else if (op != OP_SOD && op != OP_SOM && op != OP_CIRC) return FALSE;
   code += GET(code, 1);
   }
while (*code == OP_ALT);
return TRUE;
}
