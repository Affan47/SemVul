STACK_free_gosub_stack(STACK_GOSUB *gosub)
{
	int i, j;
	STACK_GOSUB *p;

	if (FP->n_ctrl)
	{
		for (i = 0, p = gosub; i < ARRAY_count(gosub); i++, p++)
		{
			for (j = 0; j < FP->n_ctrl; j++)
				RELEASE(&p->ctrl[j]);

			FREE(&p->ctrl, "STACK_free_gosub_stack");
		}
	}

	ARRAY_delete(&gosub);
}
