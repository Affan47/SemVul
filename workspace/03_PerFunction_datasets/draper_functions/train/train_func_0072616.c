elaborate(Design*des, NetScope*container) const
{
      if (direct_nested_)
	    return elaborate_direct_(des, container);

      bool flag = true;


      if (scheme_type == PGenerate::GS_CASE) {
	    if (debug_elaborate)
		  cerr << get_fileline() << ": debug: generate case"
		       << " elaborating in scope "
		       << scope_path(container) << "." << endl;

	    typedef list<PGenerate*>::const_iterator generate_it_t;
	    for (generate_it_t cur = generate_schemes.begin()
		       ; cur != generate_schemes.end() ; cur ++) {
		  PGenerate*item = *cur;
		  if (item->direct_nested_ || !item->scope_list_.empty()) {
			flag &= item->elaborate(des, container);
		  }
	    }
	    return flag;
      }

      typedef list<NetScope*>::const_iterator scope_list_it_t;
      for (scope_list_it_t cur = scope_list_.begin()
		 ; cur != scope_list_.end() ; cur ++ ) {

	    NetScope*scope = *cur;


	    if (scope->parent() != container)
		  continue;


	    const char*name = scope_name.str();
	    if (name[0] == '$') {
		  if (!scope->auto_name("genblk", '0', name + 4)) {
			cerr << get_fileline() << ": warning: Couldn't build"
			     << " unique name for unnamed generate block"
			     << " - using internal name " << name << endl;
		  }
	    }
	    if (debug_elaborate)
		  cerr << get_fileline() << ": debug: Elaborate in "
		       << "scope " << scope_path(scope) << endl;

	    flag = elaborate_(des, scope) & flag;
      }

      return flag;
}
