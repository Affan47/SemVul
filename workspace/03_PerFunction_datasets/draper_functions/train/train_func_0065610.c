scArrayJoin(const CFunctionsScopePtr &c, void *data) {
	string sep = c->getArgument("separator")->toString();
	CScriptVarPtr arr = c->getArgument("this");

	ostringstream sstr;
	int l = arr->getArrayLength();
	for (int i=0;i<l;i++) {
		if (i>0) sstr << sep;
		sstr << arr->getArrayIndex(i)->toString();
	}

	c->setReturnVar(c->newScriptVar(sstr.str()));
}
