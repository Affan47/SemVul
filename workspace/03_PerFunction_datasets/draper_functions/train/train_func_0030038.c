handle_rvalue(ir_rvalue **ir)
{
   int swizzle_chan[4];
   ir_dereference_variable *deref_var;
   ir_variable *source[4] = {NULL, NULL, NULL, NULL};
   int source_chan[4];
   int chans;

   if (!*ir)
      return;

   ir_swizzle *swizzle = (*ir)->as_swizzle();
   if (swizzle) {
      deref_var = swizzle->val->as_dereference_variable();
      if (!deref_var)
	 return;

      swizzle_chan[0] = swizzle->mask.x;
      swizzle_chan[1] = swizzle->mask.y;
      swizzle_chan[2] = swizzle->mask.z;
      swizzle_chan[3] = swizzle->mask.w;
      chans = swizzle->type->vector_elements;
   } else {
      deref_var = (*ir)->as_dereference_variable();
      if (!deref_var)
	 return;

      swizzle_chan[0] = 0;
      swizzle_chan[1] = 1;
      swizzle_chan[2] = 2;
      swizzle_chan[3] = 3;
      chans = deref_var->type->vector_elements;
   }

   if (this->in_assignee)
      return;

   ir_variable *var = deref_var->var;


   foreach_iter(exec_list_iterator, iter, *this->acp) {
      acp_entry *entry = (acp_entry *)iter.get();

      if (var == entry->lhs) {
	 for (int c = 0; c < chans; c++) {
	    if (entry->write_mask & (1 << swizzle_chan[c])) {
	       source[c] = entry->rhs;
	       source_chan[c] = entry->swizzle[swizzle_chan[c]];
	    }
	 }
      }
   }


   if (!source[0])
      return;
   for (int c = 1; c < chans; c++) {
      if (source[c] != source[0])
	 return;
   }

   if (!shader_mem_ctx)
      shader_mem_ctx = ralloc_parent(deref_var);

   if (debug) {
      printf("Copy propagation from:\n");
      (*ir)->print();
   }

   deref_var = new(shader_mem_ctx) ir_dereference_variable(source[0]);
   *ir = new(shader_mem_ctx) ir_swizzle(deref_var,
					source_chan[0],
					source_chan[1],
					source_chan[2],
					source_chan[3],
					chans);

   if (debug) {
      printf("to:\n");
      (*ir)->print();
      printf("\n");
   }
}
