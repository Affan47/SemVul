visit_enter(ir_call *ir)
{
   foreach_list_safe(n, &ir->actual_parameters) {
      ir_rvalue *param = (ir_rvalue *) n;
      ir_rvalue *new_param = convert_vector_extract_to_swizzle(param);

      if (new_param != param) {
	 param->replace_with(new_param);
      }
   }

   return visit_continue;
}
