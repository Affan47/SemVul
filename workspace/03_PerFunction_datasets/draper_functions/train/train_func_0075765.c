A_PosAttack (mobj_t* actor)
{
    int		angle;
    int		damage;
    int		slope;

    if (!actor->target)
	return;

    A_FaceTarget (actor);
    angle = actor->angle;
    slope = P_AimLineAttack (actor, angle, MISSILERANGE);

    S_StartSound (actor, sfx_pistol);
    angle += (P_Random()-P_Random())<<20;
    damage = ((P_Random()%5)+1)*3;
    P_LineAttack (actor, angle, MISSILERANGE, slope, damage);
}
