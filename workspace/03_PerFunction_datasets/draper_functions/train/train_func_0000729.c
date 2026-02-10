initialise_shutdown ()
{

    for (pipes_t::iterator it = pipes.begin (); it != pipes.end (); it ++)
        (*it)->terminate_writer ();
}
