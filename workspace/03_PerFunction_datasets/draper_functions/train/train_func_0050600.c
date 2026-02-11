delta_new(PyTypeObject *type, PyObject *args, PyObject *kw)
{
    PyObject *self = NULL;


    PyObject *day = NULL;
    PyObject *second = NULL;
    PyObject *us = NULL;
    PyObject *ms = NULL;
    PyObject *minute = NULL;
    PyObject *hour = NULL;
    PyObject *week = NULL;

    PyObject *x = NULL;
    PyObject *y = NULL;
    double leftover_us = 0.0;

    static char *keywords[] = {
        "days", "seconds", "microseconds", "milliseconds",
        "minutes", "hours", "weeks", NULL
    };

    if (PyArg_ParseTupleAndKeywords(args, kw, "|OOOOOOO:__new__",
                                    keywords,
                                    &day, &second, &us,
                                    &ms, &minute, &hour, &week) == 0)
        goto Done;

    x = PyLong_FromLong(0);
    if (x == NULL)
        goto Done;

#define CLEANUP         \
    Py_DECREF(x);       \
    x = y;              \
    if (x == NULL)      \
        goto Done

    if (us) {
        y = accum("microseconds", x, us, us_per_us, &leftover_us);
        CLEANUP;
    }
    if (ms) {
        y = accum("milliseconds", x, ms, us_per_ms, &leftover_us);
        CLEANUP;
    }
    if (second) {
        y = accum("seconds", x, second, us_per_second, &leftover_us);
        CLEANUP;
    }
    if (minute) {
        y = accum("minutes", x, minute, us_per_minute, &leftover_us);
        CLEANUP;
    }
    if (hour) {
        y = accum("hours", x, hour, us_per_hour, &leftover_us);
        CLEANUP;
    }
    if (day) {
        y = accum("days", x, day, us_per_day, &leftover_us);
        CLEANUP;
    }
    if (week) {
        y = accum("weeks", x, week, us_per_week, &leftover_us);
        CLEANUP;
    }
    if (leftover_us) {

        PyObject *temp = PyLong_FromLong(round_to_long(leftover_us));
        if (temp == NULL) {
            Py_DECREF(x);
            goto Done;
        }
        y = PyNumber_Add(x, temp);
        Py_DECREF(temp);
        CLEANUP;
    }

    self = microseconds_to_delta_ex(x, type);
    Py_DECREF(x);
Done:
    return self;

#undef CLEANUP
}
