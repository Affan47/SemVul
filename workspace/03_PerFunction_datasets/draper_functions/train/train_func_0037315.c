island_collect_node(list<vvp_branch_ptr_t>&conn, vvp_branch_ptr_t cur)
{
      conn .push_back(cur);
      for (vvp_branch_ptr_t idx = next(cur) ; idx != cur ; idx = next(idx))
	    conn.push_back(idx);
}
