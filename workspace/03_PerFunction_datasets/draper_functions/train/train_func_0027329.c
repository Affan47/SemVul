P_TryWalk(mobj_t * actor)
{
    if (!P_Move(actor))
    {
        return (false);
    }
    actor->movecount = P_Random() & 15;
    return (true);
}
