esrv_del_item(player *pl, object *ob) {
    SockList sl;

    SockList_Init(&sl);
    SockList_AddString(&sl, "delitem ");
    SockList_AddInt(&sl, ob->count);
    Send_With_Handling(&pl->socket, &sl);
    SockList_Term(&sl);


    if (pl->ob->container != NULL && ob->env == pl->ob->container)
        pl->socket.update_inventory = 1;
}
