startSimplePageSequenceHeaderFooter( unsigned hfPart ) {

    if( firstHeaderFooter ) { setupSimplePageSequence(); firstHeaderFooter = false; }

    MifDoc::TextFlow *curTextFlow;

    if( hfPart & firstHF )
        if( hfPart & frontHF )
            if( hfPart & headerHF )
                curTextFlow = FotSimplePageSequence.FirstHeaderTextFlow;
            else
                curTextFlow = FotSimplePageSequence.FirstFooterTextFlow;
        else
            return;
    else
        if( hfPart & frontHF )
            if( hfPart & headerHF )
                curTextFlow = FotSimplePageSequence.RightHeaderTextFlow;
            else
                curTextFlow = FotSimplePageSequence.RightFooterTextFlow;
        else
            if( hfPart & headerHF )
                curTextFlow = FotSimplePageSequence.LeftHeaderTextFlow;
            else
                curTextFlow = FotSimplePageSequence.LeftFooterTextFlow;

    mifDoc.enterTextFlow( *curTextFlow );

    if( hfPart & (centerHF | rightHF) )
        mifDoc.outSpecialChar( MifDoc::sTab );
    else
        (hfPart & headerHF) ? beginHeader() : beginFooter();
}
