sched_deps_init (bool global_p)
{


  int insns_in_block = sched_max_luid / n_basic_blocks + 1;

  init_deps_data_vector ();


  if (!sel_sched_p () && global_p && insns_in_block > 100 * 5)
    {


      cache_size = 0;
      extend_dependency_caches (sched_max_luid, true);
    }

  if (global_p)
    {
      dl_pool = create_alloc_pool ("deps_list", sizeof (struct _deps_list),

                                   insns_in_block);
      dn_pool = create_alloc_pool ("dep_node", sizeof (struct _dep_node),


                                   5 * insns_in_block);
    }
}
