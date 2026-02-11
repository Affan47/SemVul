SProcAuSetElements(ClientPtr client)
{
    char n;
    int i;
    auElement *e;

    REQUEST(auSetElementsReq);
    swaps(&stuff->length, n);
    swapl(&stuff->flow, n);
    swapl(&stuff->numElements, n);
    REQUEST_AT_LEAST_SIZE(auSetElementsReq);

    e = (auElement *) & stuff[1];

    for (i = 0; i < stuff->numElements; i++)
        if (!(e = SwapElement(e, AuTrue)))
            AU_ERROR(AuBadElement, e->type);

    return (*AuProcVector[stuff->reqType]) (client);
}
