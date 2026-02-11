httpHeaderInit(HttpHeader * hdr, http_hdr_owner_type owner)
{
    assert(hdr);
    assert(owner > hoNone && owner <= hoReply);
    debug(55, 7) ("init-ing hdr: %p owner: %d\n", hdr, owner);
    memset(hdr, 0, sizeof(*hdr));
    hdr->owner = owner;
    arrayInit(&hdr->entries);
}
