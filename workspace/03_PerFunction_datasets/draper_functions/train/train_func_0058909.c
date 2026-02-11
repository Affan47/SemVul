delta_cmp(PyObject *self, PyObject *other)
{
    int diff = GET_TD_DAYS(self) - GET_TD_DAYS(other);
    if (diff == 0) {
        diff = GET_TD_SECONDS(self) - GET_TD_SECONDS(other);
        if (diff == 0)
            diff = GET_TD_MICROSECONDS(self) -
                GET_TD_MICROSECONDS(other);
    }
    return diff;
}
