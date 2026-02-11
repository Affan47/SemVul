cleanup ()
{
    for (vector<gamedata*>::iterator i = saves.begin (); i != saves.end (); i++)
        delete *i;
    saves.clear ();
    unload ();
}
