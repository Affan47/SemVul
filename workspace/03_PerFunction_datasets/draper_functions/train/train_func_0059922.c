get_column(ir_dereference *val, int row)
{
   val = val->clone(mem_ctx, NULL);

   if (val->type->is_matrix()) {
      val = new(mem_ctx) ir_dereference_array(val,
					      new(mem_ctx) ir_constant(row));
   }

   return val;
}
