visit_leave(ir_assignment *ir)
{
   ir_dereference_record *lhs_rec = ir->lhs->as_dereference_record();
   if (lhs_rec) {
      ir_rvalue *lhs_rec_tmp = lhs_rec;
      handle_rvalue(&lhs_rec_tmp);
      if (lhs_rec_tmp != lhs_rec) {
         ir->set_lhs(lhs_rec_tmp);
      }
   }
   return rvalue_visit(ir);
}
