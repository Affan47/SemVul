getNextStrux(PTStruxType t) const
{
    UT_return_val_if_fail(m_pMyNode,NULL);
    pf_Fragments& fragments = m_pPieceTable->getFragments();
 	pf_Fragments::Iterator it(&(fragments),m_pMyNode);

    if( isStuxType( this, t ))
    {
        it++;
    }
    for( pf_Fragments::Iterator e = fragments.end(); it != e; ++it )
    {
        pf_Frag* pf = it.value();
        if( !pf )
            return 0;
        if( isStuxType( pf, t ))
        {
            return static_cast<pf_Frag_Strux*>(pf);
        }
    }
    return 0;
}
