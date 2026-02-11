updateTriple_add( PD_DocumentRDFMutationHandle m,
                                           const PD_URI& toModify,
                                           const PD_URI& predString,
                                           const PD_URI& explicitLinkingSubject )
{
    if( toModify.empty() )
        return;
    PD_URI pred( predString );
    m->add( explicitLinkingSubject, pred, PD_Literal(toModify.toString()), context() );
}
