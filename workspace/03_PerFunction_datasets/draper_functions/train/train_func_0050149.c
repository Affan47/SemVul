compare(const DcmElement& rhs) const
{
    if (this == &rhs)
        return 0;

    DcmElement* myThis = OFconst_cast(DcmElement*, this);
    DcmElement* myRhs = OFconst_cast(DcmElement*, &rhs);

    DcmTagKey thisKey = (*myThis).getTag().getXTag();
    DcmTagKey rhsKey = (*myRhs).getTag().getXTag();

    if ( thisKey > rhsKey )
    {
        return 1;
    }
    else if (thisKey < rhsKey)
    {
        return -1;
    }

    if ( this->ident() != rhs.ident() )
        return -1;

    return 0;
}
