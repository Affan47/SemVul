loadSymbol(ExecState* exec, bool wildcard)
{
    Package* basePackage;
    JSObject* baseObject;
    if (names) {
	PackageObject *pobj = names->resolvePackage(exec);
	if (pobj == 0)
	    return Completion(Normal);
	basePackage = pobj->package();
	baseObject = pobj;
    } else {
	Interpreter* ip = exec->lexicalInterpreter();
	basePackage = ip->globalPackage();
	baseObject = ip->globalObject();
    }

    if (wildcard) {


	PackageObject* pobj = resolvePackage(exec, baseObject, basePackage);
	if (!pobj)
	    return Completion(Normal);
	basePackage = pobj->package();
	baseObject = pobj;
	basePackage->loadAllSymbols(exec, baseObject);
    } else {
	basePackage->loadSymbol(exec, baseObject, id);
    }

    return Completion(Normal);
}
