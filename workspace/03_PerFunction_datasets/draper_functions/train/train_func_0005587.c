collector_getlines(CollectorObject *self, PyObject *args, PyObject *kw)
{
    PyObject *filename, *file_coverage_obj, *line_list_obj;
    Py_ssize_t pos = 0;
    int i;
    PyObject * results;

    results = PyDict_New();
    FileCoverage * file_coverage;
    int * line_array;
    int idx = 0;

    while (PyDict_Next(self->files, &pos, &filename, &file_coverage_obj)) {
        file_coverage = (FileCoverage *)PyCObject_AsVoidPtr(file_coverage_obj);
        line_array = file_coverage->line_array;

        idx = 0;
        for(i=0; i < DEFAULT_FILE_SIZE; i++) {
            if(line_array[i]) {
                idx++;
            }
        }
        line_list_obj = PyList_New(idx);
        idx = 0;
        for(i=0; i < DEFAULT_FILE_SIZE; i++) {
            if(line_array[i]) {
                PyList_SET_ITEM(line_list_obj, idx, PyInt_FromLong(i));
                idx++;
            }
        }
        PyDict_SetItem(results, filename, line_list_obj);
   }
   return results;
}
