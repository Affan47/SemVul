count_repr(countobject *lz)
{
    if (lz->cnt != PY_SSIZE_T_MAX)
        return PyUnicode_FromFormat("count(%zd)", lz->cnt);

    if (PyLong_Check(lz->long_step)) {
        long step = PyLong_AsLong(lz->long_step);
        if (step == -1 && PyErr_Occurred()) {
            PyErr_Clear();
        }
        if (step == 1) {

            return PyUnicode_FromFormat("count(%R)", lz->long_cnt);
        }
    }
    return PyUnicode_FromFormat("count(%R, %R)",
                                                            lz->long_cnt, lz->long_step);
}
