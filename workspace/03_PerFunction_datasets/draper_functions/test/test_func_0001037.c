ajSeqTypeIsAny(const AjPStr type_name)
{
    ajint itype;

    if(seqFindType(type_name, &itype))
	switch(seqType[itype].Type)
	{
            case ISNUC:
                return ajFalse;

            case ISPROT:
                return ajFalse;

            default:
                return ajTrue;
	}

    return ajFalse;
}
