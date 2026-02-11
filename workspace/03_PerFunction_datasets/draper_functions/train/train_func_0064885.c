ask_option(koption_t *kopt)
{
	char *s;
	printf("%s: %s ", kopt->name, kopt->desc);

	switch (kopt->type) {
		case KOPT_BOOL:
			put_bool_answer(kopt);
			break;

		case KOPT_TRISTATE:
			put_tristate_answer(kopt);
			break;

		case KOPT_INT:
			put_int_answer(kopt);
			break;

		case KOPT_STRING:
			put_string_answer(kopt);
			s = malloc(80);
			scanf("%79[^\n]\n", s);
			if (s[0] != '\0')
				kopt->def.s.v = s;
			else
				getchar();
			break;

		default:
			fprintf(stderr, "invalid option type %d\n", kopt->type);
			exit(EXIT_FAILURE);
	}
	kopt->user_set++;
}
