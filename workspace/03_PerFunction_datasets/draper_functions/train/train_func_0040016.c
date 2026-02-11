release_pipe (pipe_t *pipe_)
{
    for (pipes_t::iterator it = pipes.begin (); it != pipes.end (); it ++)
        if (*it == pipe_) {


            delete *it;


            pipes.erase (it);
            if (current == pipes.size ())
                current = 0;
            return;
        }


    assert (false);
}
