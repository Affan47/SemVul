DFS (tree name)
{
  vec<ssa_op_iter> itervec = vNULL;
  vec<tree> namevec = vNULL;
  use_operand_p usep = NULL;
  gimple defstmt;
  tree use;
  ssa_op_iter iter;

start_over:

  VN_INFO (name)->dfsnum = next_dfs_num++;
  VN_INFO (name)->visited = true;
  VN_INFO (name)->low = VN_INFO (name)->dfsnum;

  sccstack.safe_push (name);
  VN_INFO (name)->on_sccstack = true;
  defstmt = SSA_NAME_DEF_STMT (name);


  if (!gimple_nop_p (defstmt))
    {

      if (gimple_code (defstmt) == GIMPLE_PHI)
	usep = op_iter_init_phiuse (&iter, defstmt, SSA_OP_ALL_USES);
      else
	usep = op_iter_init_use (&iter, defstmt, SSA_OP_ALL_USES);
    }
  else
    clear_and_done_ssa_iter (&iter);

  while (1)
    {


      if (op_iter_done (&iter))
	{

	  if (VN_INFO (name)->low == VN_INFO (name)->dfsnum)
	    if (!extract_and_process_scc_for_name (name))
	      {
		namevec.release ();
		itervec.release ();
		return false;
	      }


	  if (namevec.is_empty ())
	    {
	      namevec.release ();
	      itervec.release ();
	      return true;
	    }


	  use = name;
	  name = namevec.pop ();
	  memcpy (&iter, &itervec.last (),
		  sizeof (ssa_op_iter));
	  itervec.pop ();
	  goto continue_walking;
	}

      use = USE_FROM_PTR (usep);


      if (TREE_CODE (use) == SSA_NAME)
	{
	  if (! (VN_INFO (use)->visited))
	    {


	      itervec.safe_push (iter);
	      namevec.safe_push (name);
	      name = use;
	      goto start_over;

continue_walking:
	      VN_INFO (name)->low = MIN (VN_INFO (name)->low,
					 VN_INFO (use)->low);
	    }
	  if (VN_INFO (use)->dfsnum < VN_INFO (name)->dfsnum
	      && VN_INFO (use)->on_sccstack)
	    {
	      VN_INFO (name)->low = MIN (VN_INFO (use)->dfsnum,
					 VN_INFO (name)->low);
	    }
	}

      usep = op_iter_next_use (&iter);
    }
}
