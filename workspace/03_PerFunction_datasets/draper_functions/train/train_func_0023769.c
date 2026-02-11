py_gc_menu_get_boards (PyObject* self, PyObject* args)
{
  GList *boards_list;
  GList *list;
  PyObject *pylist;


  if(!PyArg_ParseTuple(args, ":gcompris.get_boards_list"))
    return NULL;


  boards_list = gc_menu_get_boards();

  pylist = PyList_New(0);
  for (list = boards_list; list != NULL; list = list->next){
    PyList_Append(pylist, gcompris_new_pyGcomprisBoardObject((GcomprisBoard*) list->data));
  }

  return pylist;
}
