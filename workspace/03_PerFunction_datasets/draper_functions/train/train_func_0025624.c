RS_ResetScript (rscript_t *rs)
{
	rs_stage_t		*stage = rs->stage, *tmp_stage;
	anim_stage_t	*anim, *tmp_anim;
	random_stage_t	*randStage, *tmp_rand;

	rs->name[0] = 0;

	while (stage != NULL)
	{
		if (stage->anim_count)
		{
			anim = stage->anim_stage;
			while (anim != NULL)
			{
				tmp_anim = anim;

				anim = anim->next;
				free (tmp_anim);
			}
		}
		if (stage->rand_count)
		{
			randStage = stage->rand_stage;
			while (randStage != NULL)
			{
				tmp_rand = randStage;

				randStage = randStage->next;
				free (tmp_rand);
			}
		}

		tmp_stage = stage;
		stage = stage->next;

		free (tmp_stage);
	}

	rs->stage = NULL;
	rs->dontflush = false;
	rs->ready = false;
}
