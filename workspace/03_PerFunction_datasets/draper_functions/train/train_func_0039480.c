rb_struct_getmember(VALUE obj, ID id)
{
    VALUE members, slot, *ptr, *ptr_members;
    long i, len;

    ptr = RSTRUCT_PTR(obj);
    members = rb_struct_members(obj);
    ptr_members = RARRAY_PTR(members);
    slot = ID2SYM(id);
    len = RARRAY_LEN(members);
    for (i=0; i<len; i++) {
	if (ptr_members[i] == slot) {
	    return ptr[i];
	}
    }
    rb_name_error(id, "%s is not struct member", rb_id2name(id));
    return Qnil;
}
