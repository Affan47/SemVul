do_graft(ir_rvalue **rvalue)
{
   if (!*rvalue)
      return false;

   ir_dereference_variable *deref = (*rvalue)->as_dereference_variable();

   if (!deref || deref->var != this->graft_var)
      return false;

   if (debug) {
      printf("GRAFTING:\n");
      this->graft_assign->print();
      printf("\n");
      printf("TO:\n");
      (*rvalue)->print();
      printf("\n");
   }

   this->graft_assign->remove();
   *rvalue = this->graft_assign->rhs;

   this->progress = true;
   return true;
}
