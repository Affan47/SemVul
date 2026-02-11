cleanVObject(VObject *o)
{
    if (o == 0) return;
    if (o->prop) {


	VObject *p;
	p = o->prop->next;
	o->prop->next = 0;
	do {
	   VObject *t = p->next;
	   cleanVObject(p);
	   p = t;
	   } while (p);
	}
    switch (VALUE_TYPE(o)) {
	case VCVT_USTRINGZ:
	case VCVT_STRINGZ:
	case VCVT_RAW:

	    free((char*)STRINGZ_VALUE_OF(o));
	    break;
	case VCVT_VOBJECT:
	    cleanVObject(VOBJECT_VALUE_OF(o));
	    break;
	}
    deleteVObject(o);
}
