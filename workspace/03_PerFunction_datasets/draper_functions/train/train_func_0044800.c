getEndOfBlock( PT_DocPosition currentpos, PT_DocPosition endpos )
{
    pf_Frag *pf;
    PT_BlockOffset Offset;
    bool bFoundEndBlockBeforeEndpos = false;

    UT_DEBUGMSG(("ODTCT: getEndOfBlock() cpos:%d e:%d\n", currentpos, endpos ));


    if(getFragFromPosition( currentpos, &pf, &Offset ))
    {
        if( tryDownCastStrux( pf, PTX_Block ))
        {
            ++currentpos;
        }
    }

    for( PT_DocPosition pos = currentpos; !bFoundEndBlockBeforeEndpos && pos <= endpos; )
    {
        if(!getFragFromPosition( pos, &pf, &Offset ))
        {
            UT_DEBUGMSG(("ODTCT: getEndOfBlock() NO FRAG AT pos:%d\n", pos ));
            break;
        }

        UT_DEBUGMSG(("ODTCT: getEndOfBlock() pos:%d frag:%p len:%d frag type:%d\n", pos, pf, pf->getLength(), pf->getType() ));

        if( pf->getType() == pf_Frag::PFT_EndOfDoc )
        {
            return 0;
        }

        if( pf->getType() == pf_Frag::PFT_Strux )
        {
            PTStruxType eStruxType = static_cast<pf_Frag_Strux*>(pf)->getStruxType();
            switch (eStruxType)
            {
                case PTX_SectionFootnote:
                case PTX_SectionEndnote:
                case PTX_SectionAnnotation:
                    break;
                default:
                    return pf;
            }
        }

        pos = pf->getPos() + pf->getLength();
    }
    return 0;
}
