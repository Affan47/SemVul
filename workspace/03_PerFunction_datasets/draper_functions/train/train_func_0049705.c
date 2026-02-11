select_g_step_finish(struct step_record *step_ptr)
{
	if (slurm_select_init(0) < 0)
		return SLURM_ERROR;

	return (*(ops[select_context_default].step_finish))
		(step_ptr);
}
