vg_error_stack_to_string (VgErrorStack *stack, GString *str)
{
	timestamp_t *stamp = &stack->summary->parent->stamp;
	pid_t pid = stack->summary->parent->pid;
	int in;

	g_string_append (str, "==");
	vg_error_timestamp_to_string (stamp, str);
	g_string_append_printf (str, "%u==    %s ", pid, stack->where == VG_WHERE_AT ? "at" : "by");

	if (stack->addr != VG_STACK_ADDR_UNKNOWN)
		g_string_append_printf (str, "0x%.8x: ", stack->addr);
	else
		g_string_append (str, "<unknown address> ");

	g_string_append (str, stack->symbol ? stack->symbol : "???");

	switch (stack->type) {
	case VG_STACK_EMPTY:

		g_string_append_c (str, '\n');
		break;
	case VG_STACK_SOURCE:
		g_string_append_printf (str, " (%s:%u)\n", stack->info.src.filename, stack->info.src.lineno);
		break;
	case VG_STACK_OBJECT:
		in = !strcmp (stack->info.object + strlen (stack->info.object) - 3, ".so");
		in = in || strstr (stack->info.object, ".so.") != NULL;
		g_string_append_printf (str, " (%s %s)\n", in ? "in" : "within", stack->info.object);
		break;
	}
}
