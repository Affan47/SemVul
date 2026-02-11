PrintRG(std::stringstream& out) const {


    SamReadGroupConstIterator rgIter = m_header.ReadGroups.ConstBegin();
    SamReadGroupConstIterator rgEnd  = m_header.ReadGroups.ConstEnd();
    for ( ; rgIter != rgEnd; ++rgIter ) {
        const SamReadGroup& rg = (*rgIter);


        out << Constants::SAM_RG_BEGIN_TOKEN
            << FormatTag(Constants::SAM_RG_ID_TAG, rg.ID)
            << FormatTag(Constants::SAM_RG_SAMPLE_TAG, rg.Sample);


        if ( rg.HasLibrary() )
            out << FormatTag(Constants::SAM_RG_LIBRARY_TAG, rg.Library);


        if ( rg.HasDescription() )
            out << FormatTag(Constants::SAM_RG_DESCRIPTION_TAG, rg.Description);


        if ( rg.HasPlatformUnit() )
            out << FormatTag(Constants::SAM_RG_PLATFORMUNIT_TAG, rg.PlatformUnit);


        if ( rg.HasPredictedInsertSize() )
            out << FormatTag(Constants::SAM_RG_PREDICTEDINSERTSIZE_TAG, rg.PredictedInsertSize);


        if ( rg.HasSequencingCenter() )
            out << FormatTag(Constants::SAM_RG_SEQCENTER_TAG, rg.SequencingCenter);


        if ( rg.HasProductionDate() )
            out << FormatTag(Constants::SAM_RG_PRODUCTIONDATE_TAG, rg.ProductionDate);


        if ( rg.HasSequencingTechnology() )
            out << FormatTag(Constants::SAM_RG_SEQTECHNOLOGY_TAG, rg.SequencingTechnology);


        out << endl;
    }
}
