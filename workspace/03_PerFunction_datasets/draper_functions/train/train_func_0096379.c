py_GnumericFunc_object_dealloc (py_GnumericFunc_object *self)
{
	g_return_if_fail (self != NULL);

	gnm_func_unref (self->fn_def);
	g_free (self->eval_pos);
	PyObject_Del (self);
}
