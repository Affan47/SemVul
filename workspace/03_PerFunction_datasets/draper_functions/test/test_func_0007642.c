make_current ()
{


    if (!sockets.empty ())
        return false;

    associated = true;
    tid = thread_t::id ();
    return true;
}
