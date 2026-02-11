walk_non_aliased_vuses (ao_ref *ref, tree vuse,
			void *(*walker)(ao_ref *, tree, void *),
			void *(*translate)(ao_ref *, tree, void *), void *data)
{
  bitmap visited = NULL;
  void *res;

  timevar_push (TV_ALIAS_STMT_WALK);

  do
    {
      gimple def_stmt;


      res = (*walker) (ref, vuse, data);
      if (res)
	break;

      def_stmt = SSA_NAME_DEF_STMT (vuse);
      if (gimple_nop_p (def_stmt))
	break;
      else if (gimple_code (def_stmt) == GIMPLE_PHI)
	vuse = get_continuation_for_phi (def_stmt, ref, &visited);
      else
	{
	  if (stmt_may_clobber_ref_p_1 (def_stmt, ref))
	    {
	      if (!translate)
		break;
	      res = (*translate) (ref, vuse, data);

	      if (res == (void *)-1)
		{
		  res = NULL;
		  break;
		}

	      else if (res != NULL)
		break;

	    }
	  vuse = gimple_vuse (def_stmt);
	}
    }
  while (vuse);

  if (visited)
    BITMAP_FREE (visited);

  timevar_pop (TV_ALIAS_STMT_WALK);

  return res;
}
