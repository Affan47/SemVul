coyotename(mtmp, buf)
struct monst *mtmp;
char *buf;
{
    if (mtmp && buf) {
	Sprintf(buf, "%s - %s",
	    x_monnam(mtmp, ARTICLE_NONE, (char *)0, 0, TRUE),
	    mtmp->mcan ? coynames[SIZE(coynames)-1] : coynames[rn2(SIZE(coynames)-1)]);
    }
    return buf;
}
