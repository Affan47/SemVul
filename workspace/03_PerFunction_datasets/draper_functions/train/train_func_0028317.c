ajSeqGetBeginTrue(const AjPSeq seq)
{
    if(!seq->Begin)
	return ajSeqCalcTruepos(seq, 1);

    return ajSeqCalcTruepos(seq, seq->Begin);
}
