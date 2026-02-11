insertRow( long index, int &exceptioncode )
{


    HTMLTableSectionElementImpl* foot = tFoot();
    HTMLTableSectionElementImpl* head = tHead();
    if(!tFirstBody() && !foot && !head)
        setTBody( new HTMLTableSectionElementImpl(docPtr(), ID_TBODY, true ) );


    long sectionIndex;
    HTMLTableSectionElementImpl* section;
    if ( findRowSection( index, section, sectionIndex ) )
        return section->insertRow( sectionIndex, exceptioncode );
    else if ( index == -1 || sectionIndex == 0 )
        return section->insertRow( section->numRows(), exceptioncode );


    exceptioncode = DOMException::INDEX_SIZE_ERR;
    return 0L;
}
