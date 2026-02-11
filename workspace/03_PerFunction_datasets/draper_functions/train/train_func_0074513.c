put_state (ogzstream& out) const
{
    event::put_state (out);

    submap >> out;
    x >> out;
    y >> out;
    dir >> out;
    map >> out;

    if (c) c->get_id () >> out;
    else
    {
        string s = "";
        s >> out;
    }
}
