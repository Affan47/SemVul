as_display(char *prompt, char *fmt, ...)
{
	va_list ap;
	char *s;
	int d;
	int arg = 0;

	if (strcmp(prompt, DEBUG) == 0 && as_debug == 0)
		return;


	va_start(ap, fmt);
	as_colored_prompt(prompt);
	for (; *fmt; fmt++)
		switch (*fmt) {
		case '%':
			arg = 1;
			continue;
		case 's':
			if (arg) {
				s = va_arg(ap, char *);
				printf("%s", s);
				arg = 0;
			} else
				putchar(*fmt);
			break;
		case 'd':
			if (arg) {
				d = va_arg(ap, int);
				printf("%d", d);
				arg = 0;
			} else
				putchar(*fmt);
			break;
		case '\n':
			printf("\n");
			as_colored_prompt(prompt);
			break;
		default:
			putchar(*fmt);
		}

	va_end(ap);
	printf("\n");
	if (strcmp(prompt, LOGO))
		as_prompt();
}
