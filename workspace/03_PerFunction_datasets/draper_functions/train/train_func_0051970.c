custom_writable_update (ImplVtable *vtable, MonoBoolean do_incr, gint64 value)
{

	guint64 *ptr = (guint64 *)vtable->arg;
	if (ptr) {
		if (do_incr) {

			*ptr += value;
			return *ptr;
		}

		*ptr = value;
		return value;
	}
	return 0;
}
