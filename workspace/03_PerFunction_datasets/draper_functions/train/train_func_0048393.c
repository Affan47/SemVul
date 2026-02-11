add_dep(schedule_node *before, schedule_node *after,
			       int latency)
{
   if (!before || !after)
      return;

   assert(before != after);

   for (int i = 0; i < before->child_count; i++) {
      if (before->children[i] == after) {
	 before->child_latency[i] = MAX2(before->child_latency[i], latency);
	 return;
      }
   }

   if (before->child_array_size <= before->child_count) {
      if (before->child_array_size < 16)
	 before->child_array_size = 16;
      else
	 before->child_array_size *= 2;

      before->children = reralloc(mem_ctx, before->children,
				  schedule_node *,
				  before->child_array_size);
      before->child_latency = reralloc(mem_ctx, before->child_latency,
				       int, before->child_array_size);
   }

   before->children[before->child_count] = after;
   before->child_latency[before->child_count] = latency;
   before->child_count++;
   after->parent_count++;
}
