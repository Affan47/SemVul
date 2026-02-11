total_i(void *vstart, void *vend, size_t stride, void *ptr)
{
    VALUE v;
    struct total_data *data = (struct total_data *)ptr;

    for (v = (VALUE)vstart; v != (VALUE)vend; v += stride) {
	if (RBASIC(v)->flags) {
	    switch (BUILTIN_TYPE(v)) {
	      case T_NONE:
	      case T_ICLASS:
	      case T_NODE:
	      case T_ZOMBIE:
		continue;
	      case T_CLASS:
		if (FL_TEST(v, FL_SINGLETON))
		  continue;
	      default:
		if (data->klass == 0 || rb_obj_is_kind_of(v, data->klass)) {
		    data->total += memsize_of(v);
		}
	    }
	}
    }

    return 0;
}
