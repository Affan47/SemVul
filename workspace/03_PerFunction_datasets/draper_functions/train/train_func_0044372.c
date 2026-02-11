disconnect_vcc(VCC *vcc)
{
    ENTRY *entry;

    diag(COMPONENT,DIAG_DEBUG,"disconnected VCC 0x%p",vcc);
    entry = vcc->entry;
    discard_vcc(vcc);
    if (entry) vcc_detach(entry);
}
