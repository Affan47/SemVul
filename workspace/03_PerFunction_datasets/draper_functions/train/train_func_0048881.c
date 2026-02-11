get_event (const string & id)
{
    vector<event*>::iterator i;

    for (i = Events.begin (); i != Events.end (); i++)
         if ((*i)->id () == id) return *i;

    return NULL;
}
