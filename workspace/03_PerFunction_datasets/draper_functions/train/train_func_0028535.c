appliesToChannel(const Uint16 multiplexGroupNumber,
                                                   const Uint16 channelNumber) const
{
    OFBool result = OFTrue;
    if (!ChannelList.isEmpty())
        result = ChannelList.isElement(multiplexGroupNumber, channelNumber);
    return result;
}
