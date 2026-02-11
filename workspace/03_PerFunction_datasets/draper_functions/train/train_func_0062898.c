insert_key(uint32 keysym, int flags, const char *command)
{
    Key_Entry *newkey;
    int i, direction=-1, slot;

    slot = keysym % KEYHASH;

    if (keys[slot]==NULL) {
        keys[slot]=malloc(sizeof(Key_Entry));
        keys[slot]->command=NULL;
        keys[slot]->next=NULL;
        newkey=keys[slot];
    } else {
        newkey=keys[slot];
        while (newkey->next!=NULL)
            newkey = newkey->next;
        newkey->next = calloc(1, sizeof(Key_Entry));
        newkey = newkey->next;
    }


    for (i=0; i<9; i++)
        if (!strcmp(command, directions[i])) {
            direction=i;
            break;
        }

    newkey->keysym = keysym;
    newkey->flags = flags;
    newkey->command = strdup_local(command);
    newkey->direction = direction;
}
