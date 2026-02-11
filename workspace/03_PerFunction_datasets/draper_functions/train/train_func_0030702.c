isAtMode()
{
    SingleList* list = _connections;
    while (list) {
        ConnectInfo* cn = (ConnectInfo*) list->data;

        if (cn->mode == CLIENT_RFCOMM ||
            cn->mode == CLIENT_AT     ||
            cn->mode == CLIENT_ILIRC) {
            return EXIT_OK;
        }
        list = listSingleNext(list);
    }
    return EXIT_NOK;
}
