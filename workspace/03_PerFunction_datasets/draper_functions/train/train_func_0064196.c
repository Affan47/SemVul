visit(ir_emit_vertex *ev)
{
   foreach_list(node, this->instructions) {
      ir_instruction *ir = (ir_instruction *) node;
      ev->insert_before(ir->clone(this->mem_ctx, NULL));
   }
   return visit_continue;
}
