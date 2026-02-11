input_edge (struct lto_input_block *ib, VEC(cgraph_node_ptr, heap) *nodes,
	    bool indirect)
{
  struct cgraph_node *caller, *callee;
  struct cgraph_edge *edge;
  unsigned int stmt_id;
  gcov_type count;
  int freq;
  unsigned int nest;
  cgraph_inline_failed_t inline_failed;
  struct bitpack_d bp;
  int ecf_flags = 0;

  caller = VEC_index (cgraph_node_ptr, nodes, lto_input_sleb128 (ib));
  if (caller == NULL || caller->decl == NULL_TREE)
    internal_error ("bytecode stream: no caller found while reading edge");

  if (!indirect)
    {
      callee = VEC_index (cgraph_node_ptr, nodes, lto_input_sleb128 (ib));
      if (callee == NULL || callee->decl == NULL_TREE)
	internal_error ("bytecode stream: no callee found while reading edge");
    }
  else
    callee = NULL;

  count = (gcov_type) lto_input_sleb128 (ib);

  bp = lto_input_bitpack (ib);
  stmt_id = (unsigned int) bp_unpack_value (&bp, HOST_BITS_PER_INT);
  inline_failed = (cgraph_inline_failed_t) bp_unpack_value (&bp,
							    HOST_BITS_PER_INT);
  freq = (int) bp_unpack_value (&bp, HOST_BITS_PER_INT);
  nest = (unsigned) bp_unpack_value (&bp, 30);

  if (indirect)
    edge = cgraph_create_indirect_edge (caller, NULL, 0, count, freq, nest);
  else
    edge = cgraph_create_edge (caller, callee, NULL, count, freq, nest);

  edge->indirect_inlining_edge = bp_unpack_value (&bp, 1);
  edge->lto_stmt_uid = stmt_id;
  edge->inline_failed = inline_failed;
  edge->call_stmt_cannot_inline_p = bp_unpack_value (&bp, 1);
  edge->can_throw_external = bp_unpack_value (&bp, 1);
  if (indirect)
    {
      if (bp_unpack_value (&bp, 1))
	ecf_flags |= ECF_CONST;
      if (bp_unpack_value (&bp, 1))
	ecf_flags |= ECF_PURE;
      if (bp_unpack_value (&bp, 1))
	ecf_flags |= ECF_NORETURN;
      if (bp_unpack_value (&bp, 1))
	ecf_flags |= ECF_MALLOC;
      if (bp_unpack_value (&bp, 1))
	ecf_flags |= ECF_NOTHROW;
      if (bp_unpack_value (&bp, 1))
	ecf_flags |= ECF_RETURNS_TWICE;
      edge->indirect_info->ecf_flags = ecf_flags;
    }
}
