process_term ()
{
    zmq_assert (!shutting_down);
    shutting_down = true;

    finalise_command ();
}
