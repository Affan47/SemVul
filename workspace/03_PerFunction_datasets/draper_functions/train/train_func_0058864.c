esrv_add_spells(player *pl, object *spell) {
    SockList sl;
    size_t size;
    sstring value;

    if (!pl) {
        LOG(llevError, "esrv_add_spells, tried to add a spell to a NULL player\n");
        return;
    }

    if (!pl->socket.monitor_spells)
        return;

    SockList_Init(&sl);
    SockList_AddString(&sl, "addspell ");
    if (!spell) {
        FOR_INV_PREPARE(pl->ob, spell) {
            if (spell->type != SPELL)
                continue;


            size = 26+strlen(spell->name)+(spell->msg ? strlen(spell->msg) : 0);
            if (pl->socket.monitor_spells >= 2) {

                value = object_get_value(spell, "casting_requirements");
                size += 2 + (value ? strlen(value) : 0);
            }
            if (SockList_Avail(&sl) < size) {
                Send_With_Handling(&pl->socket, &sl);
                SockList_Reset(&sl);
                SockList_AddString(&sl, "addspell ");
            }
            append_spell(pl, &sl, spell);
        } FOR_INV_FINISH();
    } else if (spell->type != SPELL) {
        LOG(llevError, "Asked to send a non-spell object as a spell\n");
        return;
    } else
        append_spell(pl, &sl, spell);

    Send_With_Handling(&pl->socket, &sl);
    SockList_Term(&sl);
}
