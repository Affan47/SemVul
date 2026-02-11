execute (const event* e)
{
    switch (Action)
    {
        case ACTION_SCRIPT:
        {
            map_event *t = (map_event *) e;

            PyObject *args = Py_BuildValue ("(i, i, i, i, s)",
                t->submap, t->x, t->y, t->dir, t->c->get_id ().c_str ());

            Script->run (args);

            Py_DECREF (args);
            break;
        }

        case ACTION_PYFUNC:
        {
            PyFunc->callback_func0 ();
            break;
        }

        case ACTION_CPPFUNC:
        {
            Callback ();
            break;
        }

        default: break;
    }

    return do_repeat ();
}
