ProcessAlignment(const BamAlignment& al) {


    ++numReads;


    if ( al.IsDuplicate() ) ++numDuplicates;
    if ( al.IsFailedQC()  ) ++numFailedQC;
    if ( al.IsMapped()    ) ++numMapped;


    if ( al.IsReverseStrand() )
        ++numReverseStrand;
    else
        ++numForwardStrand;


    if ( al.IsPaired() ) {


        ++numPaired;


        if ( al.IsFirstMate()  ) ++numFirstMate;
        if ( al.IsSecondMate() ) ++numSecondMate;


        if ( al.IsMapped() ) {

            if ( al.IsMateMapped() )
                ++numBothMatesMapped;

            else
                ++numSingletons;
        }


        if ( al.IsProperPair() ) ++numProperPair;


        if ( settings->IsShowingInsertSizeSummary && al.IsFirstMate() && (al.InsertSize != 0) ) {
            int insertSize = abs(al.InsertSize);
            insertSizes.push_back( insertSize );
        }
    }
}
