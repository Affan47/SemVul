startSimplePageSequence() {

    inSimplePageSequence = true;
    firstHeaderFooter = true;

    bool openBookComponent = true;
    if( bookComponentOpened ) {
        if( bookComponentAvailable ) {
            openBookComponent = false;
            bookComponentAvailable = false;
        } else
            mifDoc.exitBookComponent();
    }

    if( openBookComponent ) {
        mifDoc.enterBookComponent();
        initMifBookComponent();
        bookComponentOpened = true;
        bookComponentAvailable = false;
    }

    nextFormat.FotCurDisplaySize
     = ( nextFormat.FotPageWidth - nextFormat.FotLeftMargin - nextFormat.FotRightMargin
          - nextFormat.FotPageColumnSep * ( nextFormat.FotPageNColumns - 1 ) )
        / nextFormat.FotPageNColumns;

    mifDoc.document().setDColumns( nextFormat.FotPageNColumns );
    if( nextFormat.FotPageNColumns > 1 )
        mifDoc.document().setDColumnGap( nextFormat.FotPageColumnSep );

    mifDoc.document().setProperties &= ~MifDoc::Document::fDMargins;

    start();

    FotSimplePageSequence.paragraphFormat = format();
}
