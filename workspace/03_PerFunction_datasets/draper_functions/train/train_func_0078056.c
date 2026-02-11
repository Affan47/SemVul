dumptree(Tree *tree) {
	char *name;
	if (tree == NULL)
		return "NULL";
	name = str("&T_%ulx", tree);
	if (dictget(cvars, name) == NULL) {
		switch (tree->kind) {
		    default:
			panic("dumptree: bad node kind %d", tree->kind);
		    case nWord: case nQword: case nPrim:
			print("static const Tree_s %s = { n%s, { { (char *) %s } } };\n",
			      name + 1, nodename(tree->kind), dumpstring(tree->u[0].s));
			break;
		    case nCall: case nThunk: case nVar:
			print("static const Tree_p %s = { n%s, { { (Tree *) %s } } };\n",
			      name + 1, nodename(tree->kind), dumptree(tree->u[0].p));
			break;
		    case nAssign:  case nConcat: case nClosure: case nFor:
		    case nLambda: case nLet: case nList:  case nLocal:
		    case nVarsub: case nMatch: case nExtract:
			print("static const Tree_pp %s = { n%s, { { (Tree *) %s }, { (Tree *) %s } } };\n",
			      name + 1, nodename(tree->kind), dumptree(tree->u[0].p), dumptree(tree->u[1].p));
		}
		cvars = dictput(cvars, name, tree);
	}
	return name;
}
