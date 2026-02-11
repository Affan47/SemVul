print(STD_NAMESPACE ostream &stream,
                                        const size_t flags,
                                        const char tripletSeparator,
                                        const char itemSeparator) const
{
    char buffer[64];
    const OFListConstIterator(DSRGraphicData3DItem) endPos = ItemList.end();
    OFListConstIterator(DSRGraphicData3DItem) iterator = ItemList.begin();
    while (iterator != endPos)
    {

        OFStandard::ftoa(buffer, sizeof(buffer), (*iterator).XCoord);
        stream << buffer << tripletSeparator;
        OFStandard::ftoa(buffer, sizeof(buffer), (*iterator).YCoord);
        stream << buffer << tripletSeparator;
        OFStandard::ftoa(buffer, sizeof(buffer), (*iterator).ZCoord);
        stream << buffer;
        iterator++;
        if (iterator != endPos)
        {
            if (flags & DSRTypes::PF_shortenLongItemValues)
            {
                stream << itemSeparator << "...";
                iterator = endPos;
            } else
                stream << itemSeparator;
        }
    }
    return EC_Normal;
}
