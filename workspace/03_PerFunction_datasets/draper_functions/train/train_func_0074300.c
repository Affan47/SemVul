kdb_task_state_string(const char *s)
{
	long res = 0;
	if (!s) {
		s = kdbgetenv("PS");
		if (!s)
			s = "DRSTCZEU";
	}
	while (*s) {
		switch (*s) {
		case 'D':
			res |= TASK_UNINTERRUPTIBLE;
			break;
		case 'R':
			res |= RUNNING;
			break;
		case 'S':
			res |= TASK_INTERRUPTIBLE;
			break;
		case 'T':
			res |= TASK_STOPPED;
			break;
		case 'C':
			res |= TASK_TRACED;
			break;
		case 'Z':
			res |= EXIT_ZOMBIE << 16;
			break;
		case 'E':
			res |= EXIT_DEAD << 16;
			break;
		case 'U':
			res |= UNRUNNABLE;
			break;
		case 'I':
			res |= IDLE;
			break;
		case 'M':
			res |= DAEMON;
			break;
		case 'A':
			res = ~0UL;
			break;
		default:
			  kdb_printf("%s: unknown flag '%c' ignored\n",
				     __func__, *s);
			  break;
		}
		++s;
	}
	return res;
}
