cgraph_node_for_asm (tree asmname)
{
  struct cgraph_node *node;
  void **slot;

  if (!assembler_name_hash)
    {
      assembler_name_hash =
	htab_create_ggc (10, hash_node_by_assembler_name, eq_assembler_name,
			 NULL);
      for (node = cgraph_nodes; node; node = node->next)
        if (!node->global.inlined_to)
	  {
	    tree name = DECL_ASSEMBLER_NAME (node->decl);
	    slot = htab_find_slot_with_hash (assembler_name_hash, name,
					     decl_assembler_name_hash (name),
					     INSERT);


	    if (!*slot)
	      *slot = node;
	  }
    }

  slot = htab_find_slot_with_hash (assembler_name_hash, asmname,
				   decl_assembler_name_hash (asmname),
				   NO_INSERT);

  if (slot)
    {
      node = (struct cgraph_node *) *slot;
      return node;
    }
  return NULL;
}
