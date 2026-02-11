RS_AnimateSkin (rs_stage_t *stage)
{
	anim_stage_t	*anim = stage->last_anim;


	while (stage->last_anim_time < rs_realtime)
	{
		anim = anim->next;
		if (!anim)
			anim = stage->anim_stage;
		stage->last_anim_time += stage->anim_delay;
	}

	stage->last_anim = anim;

	return anim->texture;
}
