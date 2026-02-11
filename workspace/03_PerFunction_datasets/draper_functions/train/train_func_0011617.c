streamDataPDUHead(DUL_DATAPDU * pdu, unsigned char *buf,
      unsigned long maxLength, unsigned long *rtnLen)
{
    unsigned long l;

#ifdef PDV_TEST
    if (maxLength < 18)
    {
      return makeDcmnetCondition(DULC_CODINGERROR, OF_error, "Coding Error in DUL routine: buffer too short in streamDataPDUHead");
    }

#else
    if (maxLength < 12)
    {
      return makeDcmnetCondition(DULC_CODINGERROR, OF_error, "Coding Error in DUL routine: buffer too short in streamDataPDUHead");
    }

#endif


    *buf++ = pdu->type;

    *buf++ = pdu->rsv1;

    l = pdu->length;
#ifdef PDV_TEST
    l += 6;
#endif

    COPY_LONG_BIG(l, buf);
    buf += 4;

#ifdef PDV_TEST
    l = 2;
    COPY_LONG_BIG(l, buf);
    buf += 4;
    *buf++ = pdu->presentationDataValue.presentationContextID;
    *buf++ = pdu->presentationDataValue.messageControlHeader & (~0x2);
#endif


    COPY_LONG_BIG(pdu->presentationDataValue.length, buf);
    buf += 4;

    *buf++ = pdu->presentationDataValue.presentationContextID;

    *buf++ = pdu->presentationDataValue.messageControlHeader;


    *rtnLen = 12;
#ifdef PDV_TEST
    *rtnLen = 18;
#endif

    return EC_Normal;
}
