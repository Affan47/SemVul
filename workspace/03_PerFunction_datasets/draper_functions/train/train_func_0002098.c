saveEntry(Xauth *auth)
{
    struct addrList *new;

    if (!(new = Malloc(offsetof(struct addrList, data) +
                       auth->address_length + auth->number_length)))
        return;
    new->address_length = auth->address_length;
    new->number_length = auth->number_length;
    memcpy(new->data, auth->address, (int)auth->address_length);
    memcpy(new->data + (int)auth->address_length,
           auth->number, (int)auth->number_length);
    new->family = auth->family;
    new->next = addrs;
    addrs = new;
}
