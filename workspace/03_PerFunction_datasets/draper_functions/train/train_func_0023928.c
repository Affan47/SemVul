_wrap_indicate_indicator_set_property_time(PyGObject *self, PyObject *args)
{
		double time;
		gchar *key;
		GTimeVal g_time, *g_timep;

		if (!PyArg_ParseTuple(args, "sd:Indicator.set_property_time",
							  &key, &time))
		{
				return NULL;
		}

		if (time > 0.0) {
				g_time.tv_sec = (glong) time;
				g_time.tv_usec = (glong)((time - g_time.tv_sec)
										 * G_USEC_PER_SEC);
				g_timep = &g_time;
		} else if (time == 0.0) {
				g_timep = NULL;
		} else {
				PyErr_SetString(PyExc_ValueError, "time must be >= 0.0");
				return NULL;
		}

		indicate_indicator_set_property_time(INDICATE_INDICATOR(self->obj),
											 key, g_timep);

		Py_INCREF(Py_None);
		return Py_None;
}
