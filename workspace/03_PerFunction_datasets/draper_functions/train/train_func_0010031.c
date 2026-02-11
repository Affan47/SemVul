ajSeqGetBegin(const AjPSeq seq)
{
    ajint i;
    ajint j;

    if(!seq->Begin)
	return 1;

    i = seq->Begin;

    if(seq->Begin > 0)
	i = seq->Begin - 1;

    j =  1 + ajCvtSposToPosStart(ajSeqGetLen(seq), 0, i);

    return j;
}
