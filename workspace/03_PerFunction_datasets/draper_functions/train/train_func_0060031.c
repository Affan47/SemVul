putAndInsertUint16(const DcmTag& tag,
                                        const Uint16 value,
                                        const unsigned long pos,
                                        const OFBool replaceOld)
{
    OFCondition status = EC_Normal;

    DcmElement *elem = NULL;
    switch(tag.getEVR())
    {
        case EVR_US:
            elem = new DcmUnsignedShort(tag);
            break;
        case EVR_lt:
        case EVR_xs:

            elem = new DcmUnsignedShort(DcmTag(tag, EVR_US));
            break;
        default:
            status = EC_IllegalCall;
            break;
    }
    if (elem != NULL)
    {

        status = elem->putUint16(value, pos);

        if (status.good())
            status = insert(elem, replaceOld);

        if (status.bad())
            delete elem;
    } else if (status.good())
        status = EC_MemoryExhausted;
    return status;
}
