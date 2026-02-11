A_XScream(mobj_t* actor)
{
    int sound;

    if(actor->flags & MF_NOBLOOD && actor->info->deathsound)
        sound = actor->info->deathsound;
    else
        sound = sfx_slop;

    S_StartSound(actor, sound);
}
