mondead(struct monst *mtmp)
{
    struct permonst *mptr;
    int tmp;

    if(mtmp->isgd)
    {


        if(!grddead(mtmp)) return;
    }
    lifesaved_monster(mtmp);
    if (mtmp->mhp > 0) return;


    if (mtmp == u.usteed)
            dismount_steed(DISMOUNT_GENERIC);

    mptr = mtmp->data;

    if (mtmp->cham)
            set_mon_data(mtmp, &mons[cham_to_pm[mtmp->cham]], -1);
    else if (mtmp->data == &mons[PM_WEREJACKAL])
            set_mon_data(mtmp, &mons[PM_HUMAN_WEREJACKAL], -1);
    else if (mtmp->data == &mons[PM_WEREWOLF])
            set_mon_data(mtmp, &mons[PM_HUMAN_WEREWOLF], -1);
    else if (mtmp->data == &mons[PM_WERERAT])
            set_mon_data(mtmp, &mons[PM_HUMAN_WERERAT], -1);


    tmp = monsndx(mtmp->data);
    if (mvitals[tmp].died < 255) mvitals[tmp].died++;


    if (mtmp->m_id == quest_status.leader_m_id)
            quest_status.leader_is_dead = true;
#ifdef MAIL

    if (tmp == PM_MAIL_DAEMON) mvitals[tmp].mvflags |= G_GENOD;
#endif

#ifdef KOPS
    if (mtmp->data->mlet == S_KOP)
    {

        switch(rnd(5))
        {
        case 1:
            makemon(mtmp->data,xdnstair,ydnstair,NO_MM_FLAGS);
            break;
        case 2:
            makemon(mtmp->data,0,0,NO_MM_FLAGS);
            break;
        default:
            break;
        }
    }
#endif
    if(mtmp->iswiz) wizdead();
    if(mtmp->data->msound == MS_NEMESIS) nemdead();
    if(glyph_is_invisible(levl[mtmp->mx][mtmp->my].glyph))
            unmap_object(mtmp->mx, mtmp->my);
    m_detach(mtmp, mptr);
}
