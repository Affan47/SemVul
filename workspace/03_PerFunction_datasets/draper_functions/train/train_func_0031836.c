print_evaluation_context (MonoRelationsEvaluationContext *context) {
	printf ("Context status: ");
	print_evaluation_context_status (context->status);
	if (context->status & (MONO_RELATIONS_EVALUATION_IN_PROGRESS|MONO_RELATIONS_EVALUATION_COMPLETED)) {
		print_evaluation_context_ranges (&(context->ranges));
	}
	printf ("\n");
}
