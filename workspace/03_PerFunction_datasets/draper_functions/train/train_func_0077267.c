get_state (igzstream& file)
{
    string t;
    bool b;
    u_int16 current_move__;
    s_int8 offx__, offy__;

    remove_from_pos ();

    t << file;
    load (t);


    current_move__ << file;
    previous_move << file;
    submap_ << file;
    posx_ << file;
    posy_ << file;
    offx__ << file;
    offy__ << file;

    jump_to (submap (), posx (), posy ());
    set_offset (offx__, offy__);

    current_move = current_move__;


    mypath.get_state (file);

    mypath.refmap = refmap;

    pathindex << file;
    goal_reached_ << file;


    PyObject * args;
    t << file;
    b << file;
    args = NULL;
    if (b) args = python::get_tuple (file);
    set_schedule (t, args);
    Py_XDECREF (args);
    b << file;
    set_schedule_active (b);


    t << file;
    b << file;
    args = NULL;
    if (b) args = python::get_tuple (file);
    set_action (t, args);
    Py_XDECREF (args);
    b << file;
    set_action_active (b);


    py_callback::instance = schedule.get_instance (false);
    return event_list::get_state (file);
}
