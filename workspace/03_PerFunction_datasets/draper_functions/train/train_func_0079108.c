rscorecompare(const void *aa, const void *bb)
{
    const playerentry *a = aa;
    const playerentry *b = bb;
    float ascore, bscore;
    ascore = (a->wins+(a->draws/2))/(a->wins+a->draws+a->losses);
    bscore = (b->wins+(b->draws/2))/(b->wins+b->draws+b->losses);
    if (ascore > bscore) return(-1);
    else if (bscore > ascore) return(1);
    else return(0);
}
