analyze_memory_references (void)
{
  unsigned i;
  bitmap empty;
  htab_t hempty;

  memory_accesses.refs
	  = htab_create (100, memref_hash, memref_eq, memref_free);
  memory_accesses.refs_list = NULL;
  memory_accesses.refs_in_loop = VEC_alloc (bitmap, heap,
					    number_of_loops ());
  memory_accesses.all_refs_in_loop = VEC_alloc (bitmap, heap,
						number_of_loops ());
  memory_accesses.clobbered_vops = VEC_alloc (bitmap, heap,
					      number_of_loops ());
  memory_accesses.vop_ref_map = VEC_alloc (htab_t, heap,
					   number_of_loops ());

  for (i = 0; i < number_of_loops (); i++)
    {
      empty = BITMAP_ALLOC (NULL);
      VEC_quick_push (bitmap, memory_accesses.refs_in_loop, empty);
      empty = BITMAP_ALLOC (NULL);
      VEC_quick_push (bitmap, memory_accesses.all_refs_in_loop, empty);
      empty = BITMAP_ALLOC (NULL);
      VEC_quick_push (bitmap, memory_accesses.clobbered_vops, empty);
      hempty = htab_create (10, vtoe_hash, vtoe_eq, vtoe_free);
      VEC_quick_push (htab_t, memory_accesses.vop_ref_map, hempty);
    }

  memory_accesses.ttae_cache = NULL;

  gather_mem_refs_in_loops ();
  create_vop_ref_mapping ();
}
