elaborate_sig_direct_(Design*des, NetScope*container) const
{
      if (debug_elaborate)
	    cerr << get_fileline() << ": debug: "
		 << "Direct nesting " << scope_name
		 << " (scheme_type=" << scheme_type << ")"
		 << " elaborate_sig in scope "
		 << scope_path(container) << "." << endl;


      bool flag = true;
      typedef list<PGenerate*>::const_iterator generate_it_t;
      for (generate_it_t cur = generate_schemes.begin()
		 ; cur != generate_schemes.end() ; cur ++) {
	    PGenerate*item = *cur;
	    if (item->direct_nested_ || !item->scope_list_.empty()) {

		  flag &= item->elaborate_sig(des, container);
	    }
      }
      return flag;
}
