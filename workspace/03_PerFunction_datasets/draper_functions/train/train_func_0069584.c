A_HeadAttack (mobj_t* actor)
{
    int		damage;

    if (!actor->target)
	return;

    A_FaceTarget (actor);
    if (P_CheckMeleeRange (actor))
    {
	damage = (P_Random()%6+1)*10;
	P_DamageMobj (actor->target, actor, actor, damage);
	return;
    }


    P_SpawnMissile (actor, actor->target, MT_HEADSHOT);
}
