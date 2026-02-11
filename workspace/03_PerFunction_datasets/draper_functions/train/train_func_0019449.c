esrv_new_player(player *pl, uint32 weight) {
    SockList sl;

    pl->last_weight = weight;

    if (!(pl->socket.faces_sent[pl->ob->face->number]&NS_FACESENT_FACE))
        esrv_send_face(&pl->socket, pl->ob->face->number, 0);

    SockList_Init(&sl);
    SockList_AddString(&sl, "player ");
    SockList_AddInt(&sl, pl->ob->count);
    SockList_AddInt(&sl, weight);
    SockList_AddInt(&sl, pl->ob->face->number);
    SockList_AddLen8Data(&sl, pl->ob->name, strlen(pl->ob->name));

    Send_With_Handling(&pl->socket, &sl);
    SockList_Term(&sl);
    SET_FLAG(pl->ob, FLAG_CLIENT_SENT);
}
