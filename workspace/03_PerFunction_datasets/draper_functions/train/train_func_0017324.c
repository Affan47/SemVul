reset_hostility(struct monst *roamer)
{
    if(!(roamer->isminion && (roamer->data == &mons[PM_ALIGNED_PRIEST] ||
                              roamer->data == &mons[PM_ANGEL])))
            return;

    if(EPRI(roamer)->shralign != u.ualign.type)
    {
        roamer->mpeaceful = roamer->mtame = 0;
        set_malign(roamer);
    }
    newsym(roamer->mx, roamer->my);
}
