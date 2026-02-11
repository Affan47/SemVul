py_Cell_get_value_method (py_Cell_object *self, PyObject *args)
{
	GnmEvalPos eval_pos;

	if (!PyArg_ParseTuple (args, (char *) ":get_value")) {
		return NULL;
	}

	(void) eval_pos_init_cell (&eval_pos, self->cell);
	return gnm_value_to_py_obj (&eval_pos, self->cell->value);
}
