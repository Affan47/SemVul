CreateStaticNamespace(HSQUIRRELVM v,ScriptNamespaceDecl *sn)
{
	SQInteger n = 0;
	sq_pushroottable(v);
	sq_pushstring(v,sn->name,-1);
	sq_newtable(v);
	const ScriptClassMemberDecl *members = sn->members;
	const ScriptClassMemberDecl *m = NULL;
	while(members[n].name) {
		m = &members[n];
		sq_pushstring(v,m->name,-1);
		sq_newclosure(v,m->func,0);
		sq_setparamscheck(v,m->params,m->typemask);
		sq_setnativeclosurename(v,-1,m->name);
		sq_createslot(v,-3);
		n++;
	}
	const ScriptConstantDecl *consts = sn->constants;
	const ScriptConstantDecl *c = NULL;
	n = 0;
	while(consts[n].name) {
		c = &consts[n];
		sq_pushstring(v,c->name,-1);
		switch(c->type) {
		case OT_STRING: sq_pushstring(v,c->val.s,-1);break;
		case OT_INTEGER: sq_pushinteger(v,c->val.i);break;
		case OT_FLOAT: sq_pushfloat(v,c->val.f);break;

		default: break;
		}
		sq_createslot(v,-3);
		n++;
	}
	if(sn->delegate) {

		members = sn->delegate;
		m = NULL;
		sq_newtable(v);
		while(members[n].name) {
			m = &members[n];
			sq_pushstring(v,m->name,-1);
			sq_newclosure(v,m->func,0);
			sq_setparamscheck(v,m->params,m->typemask);
			sq_setnativeclosurename(v,-1,m->name);
			sq_createslot(v,-3);
			n++;
		}
		sq_setdelegate(v,-2);
	}
	sq_createslot(v,-3);
	sq_pop(v,1);

	return TRUE;
}
