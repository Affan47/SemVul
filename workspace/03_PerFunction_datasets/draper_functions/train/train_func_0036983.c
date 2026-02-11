visit_enter(ir_loop *ir)
{
   exec_list *orig_acp = this->acp;
   exec_list *orig_kills = this->kills;
   bool orig_killed_all = this->killed_all;


   this->acp = new(mem_ctx) exec_list;
   this->kills = new(mem_ctx) exec_list;
   this->killed_all = false;

   visit_list_elements(this, &ir->body_instructions);

   if (this->killed_all) {
      orig_acp->make_empty();
   }

   exec_list *new_kills = this->kills;
   this->kills = orig_kills;
   this->acp = orig_acp;
   this->killed_all = this->killed_all || orig_killed_all;

   foreach_list(n, new_kills) {
      kill_entry *k = (kill_entry *) n;
      kill(k->var);
   }


   return visit_continue_with_parent;
}
