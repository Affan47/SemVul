possibly_null_equals(ir_instruction *a, ir_instruction *b, enum ir_node_type ignore)
{
   if (!a || !b)
      return !a && !b;

   return a->equals(b, ignore);
}
