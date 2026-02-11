nikon_prop(struct exifprop *prop, struct exiftags *t)
{
	int i;

	for (i = 0; prop->tagset[i].tag < EXIF_T_UNKNOWN &&
	    prop->tagset[i].tag != prop->tag; i++);

	if (prop->tagset[i].type && prop->tagset[i].type != prop->type)
		exifwarn2("field type mismatch", prop->name);


	if (prop->tagset[i].count && prop->tagset[i].count != prop->count)
		exifwarn2("field count mismatch", prop->name);

	if (prop->tagset == nikon_tags0) {
		nikon_prop0(prop, t);
		return;
	}

	if (prop->tagset == nikon_tags1) {
		nikon_prop1(prop, t);
		return;
	}
}
