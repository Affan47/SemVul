is_startline(const uschar *code, unsigned int bracket_map,
  unsigned int backref_map)
{
do {
   const uschar *scode = first_significant_code(code + _pcre_OP_lengths[*code],
     NULL, 0, FALSE);
   register int op = *scode;


   if (op == OP_BRA)
     {
     if (!is_startline(scode, bracket_map, backref_map)) return FALSE;
     }


   else if (op == OP_CBRA)
     {
     int n = GET2(scode, 1+LINK_SIZE);
     int new_map = bracket_map | ((n < 32)? (1 << n) : 1);
     if (!is_startline(scode, new_map, backref_map)) return FALSE;
     }


   else if (op == OP_ASSERT || op == OP_ONCE || op == OP_COND)
     { if (!is_startline(scode, bracket_map, backref_map)) return FALSE; }


   else if (op == OP_TYPESTAR || op == OP_TYPEMINSTAR || op == OP_TYPEPOSSTAR)
     {
     if (scode[1] != OP_ANY || (bracket_map & backref_map) != 0) return FALSE;
     }


   else if (op != OP_CIRC) return FALSE;


   code += GET(code, 1);
   }
while (*code == OP_ALT);
return TRUE;
}
