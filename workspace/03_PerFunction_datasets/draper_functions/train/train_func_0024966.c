schedule_instructions(backend_instruction *next_block_header)
{
   time = 0;


   foreach_list_safe(node, &instructions) {
      schedule_node *n = (schedule_node *)node;
      if (n->parent_count != 0)
	 n->remove();
   }

   unsigned cand_generation = 1;
   while (!instructions.is_empty()) {
      schedule_node *chosen = choose_instruction_to_schedule();


      assert(chosen);
      chosen->remove();
      next_block_header->insert_before(chosen->inst);
      instructions_to_schedule--;
      update_register_pressure(chosen->inst);


      time += issue_time(chosen->inst);


      time = MAX2(time, chosen->unblocked_time);

      if (debug) {
         printf("clock %4d, scheduled: ", time);
         bv->dump_instruction(chosen->inst);
      }


      for (int i = chosen->child_count - 1; i >= 0; i--) {
	 schedule_node *child = chosen->children[i];

	 child->unblocked_time = MAX2(child->unblocked_time,
				      time + chosen->child_latency[i]);

         if (debug) {
            printf("\tchild %d, %d parents: ", i, child->parent_count);
            bv->dump_instruction(child->inst);
         }

         child->cand_generation = cand_generation;
	 child->parent_count--;
	 if (child->parent_count == 0) {
            if (debug) {
               printf("\t\tnow available\n");
            }
	    instructions.push_head(child);
	 }
      }
      cand_generation++;


      if (chosen->inst->is_math()) {
	 foreach_list(node, &instructions) {
	    schedule_node *n = (schedule_node *)node;

	    if (n->inst->is_math())
	       n->unblocked_time = MAX2(n->unblocked_time,
					time + chosen->latency);
	 }
      }
   }

   assert(instructions_to_schedule == 0);
}
