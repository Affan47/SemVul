A_ClassBossHealth(mobj_t * actor)
{
    if (netgame && !deathmatch)
    {
        if (!actor->special1.i)
        {
            actor->health *= 5;
            actor->special1.i = true;
        }
    }
}
