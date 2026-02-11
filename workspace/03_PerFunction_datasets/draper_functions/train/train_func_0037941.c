gdpy_callback_func(gd_parser_data_t* pdata, void* extra)
{
  dtrace("%p, %p", pdata, extra);

  int r = GD_SYNTAX_ABORT;
  struct gdpy_dirfile_t* self = extra;

  if (self->callback != NULL) {
    char buffer[GD_MAX_LINE_LENGTH];
    gd_error_string(pdata->dirfile, buffer, GD_MAX_LINE_LENGTH);

    PyObject* arglist = Py_BuildValue("({sssisssiss}O)", "error_string", buffer,
        "suberror", pdata->suberror, "line", pdata->line, "linenum",
        pdata->linenum, "filename", pdata->filename, self->callback_data);


    if (arglist == NULL) {
      self->callback_exception = 1;
      dreturn("%i", GD_SYNTAX_ABORT);
      return GD_SYNTAX_ABORT;
    }

    PyObject* result = PyEval_CallObject(self->callback, arglist);
    Py_DECREF(arglist);


    if (result == NULL)
      self->callback_exception = 1;
    else if (PyTuple_Check(result)) {
      switch (PyTuple_Size(result))
      {
        case 0:
          PyErr_SetString(PyExc_TypeError,
              "callback must return at least one object");
          self->callback_exception = 1;
          break;
        case 1:
          r = (int)PyInt_AsLong(PyTuple_GetItem(result, 0));

          if (PyErr_Occurred()) {
            self->callback_exception = 1;
            r = GD_SYNTAX_ABORT;
          }
          break;
        default:
          r = (int)PyInt_AsLong(PyTuple_GetItem(result, 0));

          if (PyErr_Occurred()) {
            self->callback_exception = 1;
            r = GD_SYNTAX_ABORT;
          }

          char* new_string = PyString_AsString(PyTuple_GetItem(result, 1));

          if (new_string == NULL) {
            self->callback_exception = 1;
            r = GD_SYNTAX_ABORT;
          }

          strncpy(pdata->line, new_string, GD_MAX_LINE_LENGTH - 1);
          pdata->line[GD_MAX_LINE_LENGTH - 1] = '\0';
      }

      if (PyTuple_Size(result) == 1) {
      }
    } else if (PyString_Check(result)) {
      char* new_string = PyString_AsString(result);

      if (new_string == NULL) {
        self->callback_exception = 1;
        r = GD_SYNTAX_ABORT;
      }

      r = GD_SYNTAX_RESCAN;
      strncpy(pdata->line, new_string, GD_MAX_LINE_LENGTH - 1);
      pdata->line[GD_MAX_LINE_LENGTH - 1] = '\0';
    } else if (PyInt_Check(result))
      r = (int)PyInt_AsLong(result);
    else {
      PyErr_SetString(PyExc_TypeError,
          "bad return type from callback function");
      self->callback_exception = 1;
    }
  }

  dreturn("%i", r);
  return r;
}
