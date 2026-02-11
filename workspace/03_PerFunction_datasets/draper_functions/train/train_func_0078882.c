scorecompare(const void *aa, const void *bb)
{
    const playerentry *a = (const playerentry *)aa;
    const playerentry *b = (const playerentry *)bb;
    int ascore, bscore;
    ascore = 100*(a->wins+(a->draws/2))/(a->wins+a->draws+a->losses);
    bscore = 100*(b->wins+(b->draws/2))/(b->wins+b->draws+b->losses);
    if (bscore > ascore) return(1);
    else if (bscore < ascore) return(-1);
    else return(0);
}
