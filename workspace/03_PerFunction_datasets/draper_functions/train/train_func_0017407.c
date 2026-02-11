inst_free(struct inst* i) {
  jv_mem_free(i->symbol);
  block_free(i->subfn);
  block_free(i->arglist);
  if (opcode_describe(i->op)->flags & OP_HAS_CONSTANT) {
    jv_free(i->imm.constant);
  }
  jv_mem_free(i);
}
