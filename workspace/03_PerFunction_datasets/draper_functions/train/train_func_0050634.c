is_same(const tfeedback_decl &x, const tfeedback_decl &y)
{
   assert(x.is_varying() && y.is_varying());

   if (strcmp(x.var_name, y.var_name) != 0)
      return false;
   if (x.is_subscripted != y.is_subscripted)
      return false;
   if (x.is_subscripted && x.array_subscript != y.array_subscript)
      return false;
   return true;
}
