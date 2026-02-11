rb_dlptr_to_s(int argc, VALUE argv[], VALUE self)
{
    struct ptr_data *data;
    VALUE arg1, val;
    int len;

    TypedData_Get_Struct(self, struct ptr_data, &dlptr_data_type, data);
    switch (rb_scan_args(argc, argv, "01", &arg1)) {
      case 0:
	val = rb_tainted_str_new2((char*)(data->ptr));
	break;
      case 1:
	len = NUM2INT(arg1);
	val = rb_tainted_str_new((char*)(data->ptr), len);
	break;
      default:
	rb_bug("rb_dlptr_to_s");
    }

    return val;
}
