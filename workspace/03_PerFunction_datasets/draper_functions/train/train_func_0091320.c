ClassTYPEMAP_man(CTX ctx, kOutputStream *w, const knh_ClassTBL_t *ct, kNameSpace *ns)
{
	size_t i;
	int hasCaption = 0;
	kArray *typemaps = ct->typemaps;
	for(i = 0; i < typemaps->size; i++) {
		if(hasCaption == 0) {
			knh_write_ctext(ctx, w, _("TYPEMAP"));
			hasCaption = 1;
		}
		kTypeMap *mpr = typemaps->trans[i];
		knh_write_TAB(ctx, w);
		if(TypeMap_isInterface(mpr)) {
			knh_write_ascii(ctx, w, "interface ");
		}
		else {
			knh_write_ascii(ctx, w, "to ");
		}
		knh_write_cid(ctx, w, SP(mpr)->tcid);
		knh_write_EOL(ctx, w);
	}
	if(hasCaption == 1) {
		knh_write_EOL(ctx, w);
	}
}
