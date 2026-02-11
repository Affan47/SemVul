operator=(const DcmXfer &newXfer)
{
    if (this != &newXfer)
    {
        xferSyn           = newXfer.xferSyn;
        xferID            = newXfer.xferID;
        xferName          = newXfer.xferName;
        byteOrder         = newXfer.byteOrder;
        vrType            = newXfer.vrType;
        encapsulated      = newXfer.encapsulated;
        JPEGProcess8      = newXfer.JPEGProcess8;
        JPEGProcess12     = newXfer.JPEGProcess12;
        retired           = newXfer.retired;
        streamCompression = newXfer.streamCompression;
    }
    return *this;
}
