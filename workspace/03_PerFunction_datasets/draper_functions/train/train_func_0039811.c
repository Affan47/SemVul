on_prompt_completed (void *user_data)
{
	on_prompt_args *args = user_data;

	g_return_if_fail (args->op->prompting);
	gkr_debug ("%p", args->op);

	gkr_operation_unref (args->op);
	args->op->prompting = FALSE;
}
