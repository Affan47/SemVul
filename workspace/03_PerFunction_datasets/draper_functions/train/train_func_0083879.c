duplicate(const FWObject *x, bool preserve_id)
    throw(FWException)
{
    FWObject::duplicate(x, preserve_id);

    const Interface *rx = Interface::constcast(x);
    if (rx!=NULL)
    {
        bcast_bits = rx->bcast_bits;
        ostatus    = rx->ostatus;
        snmp_type  = rx->snmp_type;
    }

    return *this;
}
