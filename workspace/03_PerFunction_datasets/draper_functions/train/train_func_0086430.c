getOptions (_ScanDevice * self, PyObject * args)
{
    const SANE_Option_Descriptor *d;
    PyObject *list, *value;
    int i = 1;

    if (!PyArg_ParseTuple (args, ""))
        raiseError("Invalid arguments.");

    if (self->h == NULL)
        return raiseDeviceClosedError();

    if (!(list = PyList_New (0)))
        raiseError("Unable to allocate list.");

    do
    {
        d = sane_get_option_descriptor (self->h, i);
        if (d != NULL)
        {
            PyObject *constraint = NULL;
            int j;

            switch (d->constraint_type)
            {
            case (SANE_CONSTRAINT_NONE):
                Py_INCREF (Py_None);
                constraint = Py_None;
                break;
            case (SANE_CONSTRAINT_RANGE):
                if (d->type == SANE_TYPE_INT)
                    constraint =
                        Py_BuildValue ("iii", d->constraint.range->min,
                                       d->constraint.range->max,
                                       d->constraint.range->quant);
                else
                    constraint = Py_BuildValue ("ddd",
                                                SANE_UNFIX (d->
                                                            constraint.
                                                            range->min),
                                                SANE_UNFIX (d->
                                                            constraint.
                                                            range->max),
                                                SANE_UNFIX (d->
                                                            constraint.
                                                            range->quant));
                break;
            case (SANE_CONSTRAINT_WORD_LIST):
                constraint = PyList_New (d->constraint.word_list[0]);

                if (d->type == SANE_TYPE_INT)
                    for (j = 1; j <= d->constraint.word_list[0]; j++)
                        PyList_SetItem (constraint, j - 1,
                                        PyInt_FromLong (d->constraint.
                                                        word_list[j]));
                else
                    for (j = 1; j <= d->constraint.word_list[0]; j++)
                        PyList_SetItem (constraint, j - 1,
                                        PyFloat_FromDouble (SANE_UNFIX
                                                            (d->
                                                             constraint.
                                                             word_list[j])));
                break;
            case (SANE_CONSTRAINT_STRING_LIST):
                constraint = PyList_New (0);

                for (j = 0; d->constraint.string_list[j] != NULL; j++)
                    PyList_Append (constraint,
                                   PyString_FromString (d->constraint.
                                                        string_list[j]));
                break;
            }
            value = Py_BuildValue ("isssiiiiO", i, d->name, d->title, d->desc,
                                   d->type, d->unit, d->size, d->cap, constraint);

            PyList_Append (list, value);
        }
        i++;
    }

    while (d != NULL);
    return list;
}
