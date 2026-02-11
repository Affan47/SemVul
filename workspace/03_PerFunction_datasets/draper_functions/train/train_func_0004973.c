DealignSeq(char *seq)
{
    int aln_pos;
    int dealn_pos;

    assert(seq!=NULL);

    dealn_pos=0;
    for (aln_pos=0; aln_pos<(int)strlen(seq); aln_pos++) {
        if (! isgap(seq[aln_pos])) {
            seq[dealn_pos++] = seq[aln_pos];
        }
    }
    seq[dealn_pos] = '\0';

    return;
}
