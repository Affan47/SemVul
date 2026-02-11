visit_leave(ir_loop *ir)
{
   loop_variable_state *const ls = this->state->get(ir);


   if (ls == NULL) {
      assert(ls != NULL);
      return visit_continue;
   }

   if (ls->limiting_terminator != NULL) {


      int iterations = ls->limiting_terminator->iterations;
      if (iterations == 0) {
         ir->remove();
         this->progress = true;
         return visit_continue;
      }
   }


   foreach_list(node, &ls->terminators) {
      loop_terminator *t = (loop_terminator *) node;

      if (t->iterations < 0)
         continue;

      if (t != ls->limiting_terminator) {
         t->ir->remove();

         assert(ls->num_loop_jumps > 0);
         ls->num_loop_jumps--;

         this->progress = true;
      }
   }

   return visit_continue;
}
