union_GetOverlap (const AjPSeq first_seq,
				 const AjPSeq second_seq)
{
    const AjPStr first_seq_str = ajSeqGetSeqS(first_seq);
    const AjPStr second_seq_str = ajSeqGetSeqS(second_seq);

    ajint i = ajSeqGetLen(first_seq);

    const char * first_str = ajStrGetPtr(first_seq_str);
    const char * second_str = ajStrGetPtr(second_seq_str);

    if (i > (ajint)ajStrGetLen(second_seq_str))
	i = ajStrGetLen(second_seq_str);

    for (; i >= 0 ; --i)
	if(memcmp(&first_str[ajStrGetLen(first_seq_str)-i],second_str,i) == 0)
	    return i;

    return 0;
}
