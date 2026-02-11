aisc_c_add_to_bytes_queue(aisc_com *link, char *data, int size)
{
    struct aisc_bytes_list *bl;
    bl = (struct aisc_bytes_list *)calloc(sizeof(*bl),1);
#ifndef NDEBUG
    memset(bl, 0, sizeof(*bl));
#endif
    bl->data = data;
    bl->size = size;

    if (link->aisc_client_bytes_first){
        link->aisc_client_bytes_last->next = bl;
        link->aisc_client_bytes_last = bl;
    }else{
        link->aisc_client_bytes_first = bl;
        link->aisc_client_bytes_last = bl;
    }
}
