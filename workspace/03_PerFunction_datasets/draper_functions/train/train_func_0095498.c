Find(int id){
    uAction *run = s_playerActions;

    while (run){
        if (run->ID() == id)
            return static_cast<uActionPlayer*>(run);
        run = run->Next();
    }

    return NULL;
}
