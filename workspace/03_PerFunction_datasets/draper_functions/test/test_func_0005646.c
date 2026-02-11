incoming_call(VCC *vcc)
{
    diag(COMPONENT,DIAG_DEBUG,"incoming VCC 0x%p",vcc);
    START_TIMER(vcc->entry,REPLY);
    inarp_request(vcc->entry);
}
