A_VileTarget (mobj_t*	actor)
{
    mobj_t*	fog;

    if (!actor->target)
	return;

    A_FaceTarget (actor);

    fog = P_SpawnMobj (actor->target->x,
		       actor->target->x,
		       actor->target->z, MT_FIRE);

    actor->tracer = fog;
    fog->target = actor;
    fog->tracer = actor->target;
    A_Fire (fog);
}
