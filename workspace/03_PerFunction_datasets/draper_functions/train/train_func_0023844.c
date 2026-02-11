resolvePackage(ExecState* exec,
					       JSObject* baseObject,
					       Package* basePackage)
{
    PackageObject* res = 0;


    JSValue* v = baseObject->get(exec, id);
    if (v && !v->isUndefined()) {
	if (!v->isObject()) {

	    throwError(exec, GeneralError, "Invalid type of package %s", id);
	    return 0;
	}
	res = static_cast<PackageObject*>(v);
    } else {
	UString err;
	Package *newBase = basePackage->loadSubPackage(id, &err);
	if (newBase == 0) {
	    if (err.isEmpty()) {
		throwError(exec, GeneralError, "Package not found");
	    } else {
		throwError(exec, GeneralError, err);
	    }
	    return 0;
	}
	res = new PackageObject(newBase);
	baseObject->put(exec, id, res);
    }

    return res;
}
