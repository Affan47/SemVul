attribute_read(Stream *htio, classfile *clazz)
{
	attrib_info *a;
	u4 len;
	char *aname;

	a = ht_malloc(sizeof (*a));
	if (!a) {
		return NULL;
	}
	a->offset    = offset;
	a->name      = READ2();
	a->len = len = READ4();

	aname = get_string(htio, clazz, a->name);
	if (!strcmp (aname, "ConstantValue")) {
		a->tag = ATTRIB_ConstantValue;
	} else if (!strcmp(aname, "Code")) {
		a->tag = ATTRIB_Code;
		a->code.max_stack = READ2();
		a->code.max_locals = READ2();
		a->code.len = READ4();
		a->code.start = offset;
		len -= 2+2+4+a->code.len;
		SKIPN(a->code.len);
		a->code.exctbl_len = READ2();
		if (a->code.exctbl_len) {
			a->code.exctbl = ht_malloc(a->code.exctbl_len * sizeof(exception_info));
			for (uint i=0; i < a->code.exctbl_len; i++) {
				a->code.exctbl[i].start_pc = READ2();
				a->code.exctbl[i].end_pc = READ2();
				a->code.exctbl[i].handler_pc = READ2();
				a->code.exctbl[i].catch_type = READ2();
			}
		}
		len -= 2 + 8*a->code.exctbl_len;
	} else if (!strcmp(aname, "Signature")) {
		a->tag = ATTRIB_Signature;
		a->signature = READ2();
		len -= 2;
	} else if (!strcmp(aname, "Exceptions")) {
		a->tag = ATTRIB_Exceptions;
	} else if (!strcmp(aname, "InnerClasses")) {
		a->tag = ATTRIB_InnerClasses;
	} else if (!strcmp(aname, "Synthetic")) {
		a->tag = ATTRIB_Synthetic;
	} else if (!strcmp(aname, "SourceFile")) {
		a->tag = ATTRIB_SourceFile;
	} else if (!strcmp(aname, "LineNumberTable")) {
		a->tag = ATTRIB_LineNumberTable;
	} else if (!strcmp(aname, "LocalVariableTable")) {
		a->tag = ATTRIB_LocalVariableTable;
	} else if (!strcmp(aname, "Deprecated")) {
		a->tag = ATTRIB_Deprecated;
	}
	SKIPN(len);
	return (a);
}
