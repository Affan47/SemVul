putUint8Array(const Uint8 *byteValue,
                                                 const unsigned long numBytes)
{
    errorFlag = EC_Normal;
    if (numBytes > 0)
    {

        if ((byteValue != NULL) && (getTag().getEVR() != EVR_OW && getTag().getEVR() != EVR_lt))
        {
            errorFlag = putValue(byteValue, sizeof(Uint8) * OFstatic_cast(Uint32, numBytes));
            alignValue();
        } else
            errorFlag = EC_CorruptedData;
    } else
        putValue(NULL, 0);
    return errorFlag;
}
