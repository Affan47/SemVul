write_ratio_db(PyObject *self, PyObject *args){
    PyObject *ratio_dict;
    PyObject *dict_key, *dict_value;
    DBT key, data;
    DB *rdb;
    double ratio;
    simprof sp;
    Py_ssize_t ppos;
    int i;
    DB_BTREE_STAT *stat;

    memset(&key, 0, sizeof(key));
    memset(&data, 0, sizeof(data));

    if(!PyArg_ParseTuple(args, "O", &ratio_dict))
        return NULL;
    Py_INCREF(ratio_dict);

    printf("dict_check: %d\n", PyDict_Check(ratio_dict));
    printf("dict_size: %d\n", (int)PyDict_Size(ratio_dict));

    sqlite_db_env_open(NULL);
    sqlite_db_primary_open(&rdb, "ratios", DB_BTREE, 4*1024, DB_CREATE, 0, NULL);
    printf("opened db!\n");

    ppos = 0;
    while(PyDict_Next(ratio_dict, &ppos, &dict_key, &dict_value)){
        for(i=0; i < NUM_COMPS; ++i){
           *(int*)(((char*)&sp)+sp_offsets[i]) = (int)PyInt_AsLong(PyTuple_GetItem(dict_key, (Py_ssize_t)i));
        }
        ratio = PyFloat_AsDouble(dict_value);

        key.data = &sp;
        key.size = sizeof(sp);
        data.data = &ratio;
        data.size = sizeof(double);

        rdb->put(rdb, NULL, &key, &data, 0);
    }

    rdb->stat(rdb, NULL, &stat, 0);

    free(stat);

    rdb->close(rdb, 0);
    sqlite_db_env_close();

    Py_DECREF(ratio_dict);
    Py_INCREF(Py_None);
    return Py_None;
}
