readPDUHead(PRIVATE_ASSOCIATIONKEY ** association,
            unsigned char *buffer, unsigned long maxLength,
            DUL_BLOCKOPTIONS block, int timeout,
            unsigned char *PDUType, unsigned char *PDUReserved,
            unsigned long *PDULength)
{

    OFCondition cond = EC_Normal;


    if ((*association)->inputPDU == NO_PDU)
    {

        cond = readPDUHeadTCP(association, buffer, maxLength, block, timeout,
             &(*association)->nextPDUType, &(*association)->nextPDUReserved, &(*association)->nextPDULength);
    }

    if (cond.good()) {

        (*association)->inputPDU = PDU_HEAD;


        *PDUType = (*association)->nextPDUType;
        *PDUReserved = (*association)->nextPDUReserved;
        *PDULength = (*association)->nextPDULength;


        if ((*PDUType == DUL_TYPEDATA) && (*PDULength > (*association)->maxPDVInput))
        {
          char buf1[256];
          sprintf(buf1, "DUL Illegal PDU Length %ld.  Max expected %ld", *PDULength, (*association)->maxPDVInput);
          cond = makeDcmnetCondition(DULC_ILLEGALPDULENGTH, OF_error, buf1);
        }
    }


    return cond;
}
