P_ExplodeMissile(mobj_t * mo)
{
    mo->momx = mo->momy = mo->momz = 0;
    P_SetMobjState(mo, mobjinfo[mo->type].deathstate);

    mo->flags &= ~MF_MISSILE;

    switch (mo->type)
    {
        case MT_SORCBALL1:
        case MT_SORCBALL2:
        case MT_SORCBALL3:
            S_StartSound(NULL, SFX_SORCERER_BIGBALLEXPLODE);
            break;
        case MT_SORCFX1:
            S_StartSound(NULL, SFX_SORCERER_HEADSCREAM);
            break;
        default:
            if (mo->info->deathsound)
            {
                S_StartSound(mo, mo->info->deathsound);
            }
            break;
    }
}
