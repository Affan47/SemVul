printGeneralNodeError(const DSRXMLCursor &cursor,
                                           const OFCondition &result) const
{

    if (result.bad())
    {
        OFString tmpString;
        DCMSR_ERROR("Parsing node " << getFullNodePath(cursor, tmpString) << " (" << result.text() << ")");
    }
}
