yelp(struct monst *mtmp)
{
    const char *yelp_verb = 0;

    if (mtmp->msleeping || !mtmp->mcanmove || !mtmp->data->msound)
            return;


    if (Hallucination)
            yelp_verb = h_sounds[rn2(SIZE(h_sounds))];
    else switch (mtmp->data->msound)
    {
    case MS_MEW:
        yelp_verb = "yowl";
        break;
    case MS_BARK:
    case MS_GROWL:
        yelp_verb = "yelp";
        break;
    case MS_ROAR:
        yelp_verb = "snarl";
        break;
    case MS_SQEEK:
        yelp_verb = "squeal";
        break;
    case MS_SQAWK:
        yelp_verb = "screak";
        break;
    case MS_WAIL:
        yelp_verb = "wail";
        break;
    }
    if (yelp_verb)
    {
        pline("%s %s!", Monnam(mtmp), vtense((char *)0, yelp_verb));
        if(flags.run) nomul(0);
        wake_nearto(mtmp->mx, mtmp->my, mtmp->data->mlevel * 12);
    }
}
