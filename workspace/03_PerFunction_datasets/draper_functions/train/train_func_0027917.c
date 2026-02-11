A_Chase(mobj_t * actor)
{
    int delta;

    if (actor->reactiontime)
    {
        actor->reactiontime--;
    }


    if (actor->threshold)
    {
        actor->threshold--;
    }

    if (gameskill == sk_nightmare)
    {
        actor->tics -= actor->tics / 2;
        if (actor->tics < 3)
        {
            actor->tics = 3;
        }
    }


    if (actor->movedir < 8)
    {
        actor->angle &= (7 << 29);
        delta = actor->angle - (actor->movedir << 29);
        if (delta > 0)
        {
            actor->angle -= ANG90 / 2;
        }
        else if (delta < 0)
        {
            actor->angle += ANG90 / 2;
        }
    }

    if (!actor->target || !(actor->target->flags & MF_SHOOTABLE))
    {
        if (P_LookForPlayers(actor, true))
        {
            return;
        }
        P_SetMobjState(actor, actor->info->spawnstate);
        return;
    }


    if (actor->flags & MF_JUSTATTACKED)
    {
        actor->flags &= ~MF_JUSTATTACKED;
        if (gameskill != sk_nightmare)
            P_NewChaseDir(actor);
        return;
    }


    if (actor->info->meleestate && P_CheckMeleeRange(actor))
    {
        if (actor->info->attacksound)
        {
            S_StartSound(actor, actor->info->attacksound);
        }
        P_SetMobjState(actor, actor->info->meleestate);
        return;
    }


    if (actor->info->missilestate)
    {
        if (gameskill < sk_nightmare && actor->movecount)
            goto nomissile;
        if (!P_CheckMissileRange(actor))
            goto nomissile;
        P_SetMobjState(actor, actor->info->missilestate);
        actor->flags |= MF_JUSTATTACKED;
        return;
    }
  nomissile:


    if (netgame && !actor->threshold && !P_CheckSight(actor, actor->target))
    {
        if (P_LookForPlayers(actor, true))
            return;
    }


    if (--actor->movecount < 0 || !P_Move(actor))
    {
        P_NewChaseDir(actor);
    }


    if (actor->info->activesound && P_Random() < 3)
    {
        if (actor->type == MT_BISHOP && P_Random() < 128)
        {
            S_StartSound(actor, actor->info->seesound);
        }
        else if (actor->type == MT_PIG)
        {
            S_StartSound(actor, SFX_PIG_ACTIVE1 + (P_Random() & 1));
        }
        else if (actor->flags2 & MF2_BOSS)
        {
            S_StartSound(NULL, actor->info->activesound);
        }
        else
        {
            S_StartSound(actor, actor->info->activesound);
        }
    }
}
