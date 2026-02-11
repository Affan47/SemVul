SaveNextAlignment(BamReader* reader, BamAlignment* alignment) {


    if ( m_isCoreMode && m_sort.isTagCoreAttribute()) {
        if ( reader->GetNextAlignmentCore(*alignment) )
            m_alignments->Add( make_pair(reader, alignment) );
    }


    else {
        if ( reader->GetNextAlignment(*alignment) )
            m_alignments->Add( make_pair(reader, alignment) );
    }
}
