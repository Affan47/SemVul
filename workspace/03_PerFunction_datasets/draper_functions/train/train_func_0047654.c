viewLayerNameFromID(ViewLayerID viewLayerID) {
	NamePair * sp = names.value(viewLayerID);
	if (sp == NULL) return ___emptyString___;

	return sp->displayName;
}
