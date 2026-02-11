gnm_python_destroy_interpreter (GnmPython *gpy, GnmPyInterpreter *interpreter)
{
	g_return_if_fail (IS_GNM_PYTHON (gpy));
	g_return_if_fail (IS_GNM_PY_INTERPRETER (interpreter));
	g_return_if_fail (interpreter != gpy->default_interpreter);

	GO_SLIST_REMOVE (gpy->interpreters, interpreter);
	gnm_py_interpreter_destroy (interpreter, gpy->default_interpreter);
	g_object_unref (gpy);
}
