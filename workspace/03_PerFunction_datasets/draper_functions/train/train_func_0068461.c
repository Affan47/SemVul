push_if_stack(struct brw_compile *p, struct brw_instruction *inst)
{
   p->if_stack[p->if_stack_depth] = inst - p->store;

   p->if_stack_depth++;
   if (p->if_stack_array_size <= p->if_stack_depth) {
      p->if_stack_array_size *= 2;
      p->if_stack = reralloc(p->mem_ctx, p->if_stack, int,
			     p->if_stack_array_size);
   }
}
