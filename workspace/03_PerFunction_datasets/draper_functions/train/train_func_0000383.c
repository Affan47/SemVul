allot_array_1(CELL obj)
{
	REGISTER_ROOT(obj);
	F_ARRAY *a = allot_array_internal(ARRAY_TYPE,1);
	UNREGISTER_ROOT(obj);
	set_array_nth(a,0,obj);
	return tag_object(a);
}
