DXGetNextHashElement( HashTable hashtab )
{
    PageTable * pagetab;
    HashElement element, nextelt;
    HashElement *pages;
    int pageNum, eltNum;
    int eltSize, eltsInPage;
    int nPages;

    if ( ! hashtab )
        return ERROR;

    pagetab = &hashtab->pageTable;

    if ( ( pageNum = hashtab->getNextPage ) >= ( nPages = pagetab->nPages ) )
        return NULL;

    eltNum = hashtab->getNextElement;
    pages = pagetab->pagePtrs;
    eltSize = pagetab->eltSize;

    if ( pageNum == nPages - 1 )
        eltsInPage = pagetab->nextEltNum;
    else
        eltsInPage = ELTS_PER_PAGE;

    nextelt = ( HashElement ) ( ( ( char * ) pages[ pageNum ] ) + eltNum * eltSize );

    while ( pageNum < nPages ) {
        element = nextelt;
        eltNum ++;

        if ( eltNum >= eltsInPage ) {
            eltNum = 0;

            if ( ++pageNum < nPages ) {
                if ( pageNum == nPages - 1 )
                    eltsInPage = pagetab->nextEltNum;
                else
                    eltsInPage = ELTS_PER_PAGE;

                nextelt = pages[ pageNum ];
            }
        } else
            nextelt = ( HashElement ) ( ( char * ) element + eltSize );

        if ( element->u.pseudoKey ) {
            hashtab->getNextPage = pageNum;
            hashtab->getNextElement = eltNum;
            return DATA_PTR( element );
        }
    }
    return NULL;
}
