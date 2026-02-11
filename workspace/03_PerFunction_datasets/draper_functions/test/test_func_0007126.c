csn_compare_ext(const CSN *csn1, const CSN *csn2, unsigned int flags)
{
    PRInt32 retVal;
	if(csn1!=NULL && csn2!=NULL)
	{


        if (csn1->tstamp < csn2->tstamp)
            retVal = -1;
        else if (csn1->tstamp > csn2->tstamp)
            retVal = 1;
        else
        {
            if (csn1->seqnum < csn2->seqnum)
                retVal = -1;
            else if (csn1->seqnum > csn2->seqnum)
                retVal = 1;
            else
            {
                if (csn1->rid < csn2->rid)
                    retVal = -1;
                else if (csn1->rid > csn2->rid)
                    retVal = 1;
                else if (!(flags & CSN_COMPARE_SKIP_SUBSEQ))
                {
                    if (csn1->subseqnum < csn2->subseqnum)
                        retVal = -1;
                    else if (csn1->subseqnum > csn2->subseqnum)
                        retVal = 1;
                    else
                        retVal = 0;
                }
                else
                    retVal = 0;
            }
        }

	}
	else if(csn1!=NULL && csn2==NULL)
	{
		retVal= 1;
	}
	else if (csn1==NULL && csn2!=NULL)
	{
		retVal= -1;
	}
	else
	{
		retVal= 0;
	}

    return(retVal);
}
