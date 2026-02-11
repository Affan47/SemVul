ajSeqBamDel(AjPSeqBam *Pbam)
{
    AjPSeqBam bam = NULL;

    bam = *Pbam;

    if(bam == 0)
        return;

    AJFREE(bam->data);
    AJFREE(*Pbam);

    return;
}
