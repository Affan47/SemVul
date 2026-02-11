print_evaluation_context_status (MonoRelationsEvaluationStatus status) {
	if (status == MONO_RELATIONS_EVALUATION_NOT_STARTED) {
		printf ("EVALUATION_NOT_STARTED");
	} else {
		gboolean print_or = FALSE;

		printf ("(");
		if (status & MONO_RELATIONS_EVALUATION_IN_PROGRESS) {
			if (print_or) printf ("|");
			printf ("EVALUATION_IN_PROGRESS");
			print_or = TRUE;
		}
		if (status & MONO_RELATIONS_EVALUATION_COMPLETED) {
			if (print_or) printf ("|");
			printf ("EVALUATION_COMPLETED");
			print_or = TRUE;
		}
		if (status & MONO_RELATIONS_EVALUATION_IS_RECURSIVELY_ASCENDING) {
			if (print_or) printf ("|");
			printf ("RECURSIVELY_ASCENDING");
			print_or = TRUE;
		}
		if (status & MONO_RELATIONS_EVALUATION_IS_RECURSIVELY_DESCENDING) {
			if (print_or) printf ("|");
			printf ("RECURSIVELY_DESCENDING");
			print_or = TRUE;
		}
		if (status & MONO_RELATIONS_EVALUATION_IS_RECURSIVELY_INDEFINITE) {
			if (print_or) printf ("|");
			printf ("RECURSIVELY_INDEFINITE");
			print_or = TRUE;
		}
		printf (")");
	}
}
