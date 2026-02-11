name_to_object(const char *name, GLEJustify* just) throw(ParserError) {
	char str[80];
	int idx, type;
	GLEString sname(name);
	GLERC<GLEArrayImpl> path(sname.split('.'));
	GLEString* objname = (GLEString*)path->getObjectUnsafe(0);
	objname->toUTF8(str);
	getVars()->find(str, &idx, &type);
	if (idx != -1) {
		GLEDataObject* obj = getVars()->getObject(idx);
		if (obj != NULL && obj->getType() == GLEObjectTypeObjectRep) {
			return name_to_object((GLEObjectRepresention*)obj, path.get(), just, 1);
		} else {
			string err = getVars()->typeError(idx, GLEObjectTypeObjectRep);
			g_throw_parser_error(err);
		}
	} else {
		GLEObjectRepresention* obj = getCRObjectRep();
		if (obj->isChildObjectsEnabled()) {
			return name_to_object(obj, path.get(), just, 0);
		} else {
			ostringstream str;
			str << "name '" << *objname << "' not defined";
			g_throw_parser_error(str.str());
		}
	}
	return NULL;
}
