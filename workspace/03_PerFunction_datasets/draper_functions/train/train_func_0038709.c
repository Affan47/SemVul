SProcAuWriteElement(ClientPtr client)
{
    char n;

    REQUEST(auWriteElementReq);
    swaps(&stuff->length, n);
    swapl(&stuff->flow, n);
    swapl(&stuff->num_bytes, n);
    REQUEST_AT_LEAST_SIZE(auWriteElementReq);
    return (*AuProcVector[stuff->reqType]) (client);
}
