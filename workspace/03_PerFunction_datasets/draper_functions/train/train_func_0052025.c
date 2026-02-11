DGNGetAttrLinkSize( DGNHandle hDGN, DGNElemCore *psElement,
                        int nOffset )

{
    if( psElement->attr_bytes < nOffset + 4 )
        return 0;


    if( (psElement->attr_data[nOffset+0] == 0
         && psElement->attr_data[nOffset+1] == 0)
        || (psElement->attr_data[nOffset+0] == 0
            && psElement->attr_data[nOffset+1] == 0x80) )
        return 8;


    if( psElement->attr_data[nOffset+1] & 0x10 )
        return psElement->attr_data[nOffset+0] * 2 + 2;


    return 0;
}
