declared_type(const String &name, int scope_cookie) const
{
    for (const RouterT *r = this; r; scope_cookie = r->_declaration_scope_cookie, r = r->_declaration_scope)
	for (int i = r->_declared_type_map[name]; i >= 0; i = r->_declared_types[i].prev_name)
	    if (r->_declared_types[i].scope_cookie <= scope_cookie)
		return r->_declared_types[i].type;
    return 0;
}
