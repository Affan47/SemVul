get_scope_var_name(PHP_SCOPE_TABLE scope, PHP_VAR_NODE *var)
{
	PHP_SCOPE_TABLE_TYPE *scope_map = (PHP_SCOPE_TABLE_TYPE *)scope;


#if 0
	for(PHP_SCOPE_TABLE_TYPE::iterator i = scope_map->begin(); i != scope_map->end();i++) {
#else
	for(PHP_SCOPE_TABLE_TYPE::iterator i = scope_map->begin(); i != scope_map->end();++i) {
#endif

		if ( i->second->type == PHP_SCOPE_VAR ) {
			PHP_VAR_NODE *curr_var = i->second->var;
			if ( curr_var == var ) {
				return i->first.c_str();
			}
		}
	}
	return 0;
}
