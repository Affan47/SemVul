rb_struct_each_pair(s)
    VALUE s;
{
    VALUE members;
    long i;

    members = rb_struct_members(s);
    for (i=0; i<RSTRUCT(s)->len; i++) {
	rb_yield_values(2, rb_ary_entry(members, i), RSTRUCT(s)->ptr[i]);
    }
    return s;
}
