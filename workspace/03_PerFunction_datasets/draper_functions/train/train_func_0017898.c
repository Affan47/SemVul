ProcAuListBuckets(ClientPtr client)
{
    REQUEST(auReq);
    auListBucketsReply rep;
    auBucketAttributes a, *match;
    ComponentPtr c;
    int nbuckets, len;

    REQUEST_AT_LEAST_SIZE(auReq);
    len = (stuff->length << 2) - sizeof(auReq) -
            sizeof(auBucketAttributes);

    if (len < 0)
        AU_ERROR(AuBadLength, 0);

    match = (auBucketAttributes *) & stuff[1];

    if (match->common.value_mask & AuCompCommonDescriptionMask)
        if (len != PAD4(match->common.description.len))
            AU_ERROR(AuBadLength, 0);

    c = auBuckets;
    nbuckets = len = 0;


    while (c) {
        c->list = !c->destroyed &&
                (CLIENT_ID(c->id) == client->index ||
                 c->access & AuAccessListMask) &&
                AuMatchAttributes(match, c, &match[1]);

        if (c->list) {
            nbuckets++;
            len += PAD4(c->description.len);
        }

        c = c->next;
    }


    rep.type = Au_Reply;
    rep.sequenceNumber = client->sequence;
    rep.length = (sizeof(auBucketAttributes) * nbuckets + len) >> 2;
    rep.num_buckets = nbuckets;
    WriteAuReplyToClient(client, sizeof(rep), &rep);

    c = auBuckets;

    while (c) {
        if (c->list) {
            xferBucketAttributes(c, a);

            WriteAuSwappedDataToClient(client, sizeof(a), &a,
                                       AuSwapBucketAttributesWrite);
            (void) WriteToClient(client, c->description.len,
                                 c->description.string);
        }

        c = c->next;
    }

    return client->noClientException;
}
