add_to_pack(object *obj, object *pack, int condense)
{
    object *op, *p;

    if (condense) {
	if ((op = check_duplicate(obj, pack))) {
	    free_object(obj);
	    return op;
	} else {
	    obj->ichar = next_avail_ichar();
	}
    }
#if !defined( ORIGINAL )
    for (op = pack; op->next_object; op = op->next_object) {
	if (op->next_object->what_is > obj->what_is) {
	    p = op->next_object;
	    op->next_object = obj;
	    obj->next_object = p;
	    return obj;
	}
    }
    op->next_object = obj;
    obj->next_object = 0;
    return obj;
#else
    if (pack->next_object == 0) {
	pack->next_object = obj;
    } else {
	op = pack->next_object;

	while (op->next_object) {
	    op = op->next_object;
	}
	op->next_object = obj;
    }
    obj->next_object = 0;
    return obj;
#endif
}
