ProcAuGetElements(ClientPtr client)
{
    REQUEST(auResourceReq);
    auGetElementsReply rep;
    FlowPtr flow;
    int i;

    REQUEST_SIZE_MATCH(auResourceReq);

    if (!(flow = (FlowPtr) LookupIDByType(stuff->id, auFlowType)))
        AU_ERROR(AuBadFlow, stuff->id);


    rep.type = Au_Reply;
    rep.sequenceNumber = client->sequence;
    rep.length =
            (sizeof(auElement) * flow->numElements + flow->varLen) >> 2;
    rep.flow = flow->flowId;
    rep.clocked = flow->clocked;
    rep.num_elements = flow->numElements;
    WriteAuReplyToClient(client, sizeof(rep), &rep);

    for (i = 0; i < flow->numElements; i++)
        WriteAuSwappedDataToClient(client,
                                   flow->elements[i].varLen +
                                   sizeof(auElement),
                                   flow->elements[i].raw,
                                   AuCopySwapElementWrite);

    return AuSuccess;
}
