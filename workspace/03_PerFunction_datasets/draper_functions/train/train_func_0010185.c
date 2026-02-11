insertEmptyElement(const DcmTag& tag,
                                        const OFBool replaceOld)
{
    OFCondition status = EC_Normal;

    DcmElement *elem = NULL;
    switch(tag.getEVR())
    {
        case EVR_AE:
            elem = new DcmApplicationEntity(tag);
            break;
        case EVR_AS:
            elem = new DcmAgeString(tag);
            break;
        case EVR_AT:
            elem = new DcmAttributeTag(tag);
            break;
        case EVR_CS:
            elem = new DcmCodeString(tag);
            break;
        case EVR_DA:
            elem = new DcmDate(tag);
            break;
        case EVR_DS:
            elem = new DcmDecimalString(tag);
            break;
        case EVR_DT:
            elem = new DcmDateTime(tag);
            break;
        case EVR_FL:
            elem = new DcmFloatingPointSingle(tag);
            break;
        case EVR_FD:
            elem = new DcmFloatingPointDouble(tag);
            break;
        case EVR_IS:
            elem = new DcmIntegerString(tag);
            break;
        case EVR_LO:
            elem = new DcmLongString(tag);
            break;
        case EVR_LT:
            elem = new DcmLongText(tag);
            break;
        case EVR_OB:
        case EVR_OW:
            elem = new DcmOtherByteOtherWord(tag);
            break;
        case EVR_OD:
            elem = new DcmOtherDouble(tag);
            break;
        case EVR_OF:
            elem = new DcmOtherFloat(tag);
            break;
        case EVR_PN:
            elem = new DcmPersonName(tag);
            break;
        case EVR_SH:
            elem = new DcmShortString(tag);
            break;
        case EVR_SL:
            elem = new DcmSignedLong(tag);
            break;
        case EVR_SQ:
            elem = new DcmSequenceOfItems(tag);
            break;
        case EVR_SS:
            elem = new DcmSignedShort(tag);
            break;
        case EVR_ST:
            elem = new DcmShortText(tag);
            break;
        case EVR_TM:
            elem = new DcmTime(tag);
            break;
        case EVR_UI:
            elem = new DcmUniqueIdentifier(tag);
            break;
        case EVR_UL:
            elem = new DcmUnsignedLong(tag);
            break;
        case EVR_US:
            elem = new DcmUnsignedShort(tag);
            break;
        case EVR_UT:
            elem = new DcmUnlimitedText(tag);
            break;
        default:
            status = EC_IllegalCall;
            break;
    }
    if (elem != NULL)
    {

        status = insert(elem, replaceOld);

        if (status.bad())
            delete elem;
    } else if (status.good())
        status = EC_MemoryExhausted;
    return status;
}
