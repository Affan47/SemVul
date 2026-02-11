A_FaceTarget (mobj_t* actor)
{
    if (!actor->target)
        return;

    actor->flags &= ~MF_AMBUSH;

    actor->angle = R_PointToAngle2 (actor->x,
                                    actor->y,
                                    actor->target->x,
                                    actor->target->y);

    if(actor->target->flags & MF_SHADOW)
    {

        int t = P_Random();
        actor->angle += (t - P_Random()) << 22;
    }
    else if(actor->target->flags & MF_MVIS)
    {

        int t = P_Random();
        actor->angle += (t - P_Random()) << 23;
    }
}
