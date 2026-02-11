set_flag_from_env (int flag, const char *s, int neg)
{
    char *e = getenv(s);
    int action = 0;

    if (e != NULL) {
	if (*e != '\0' && *e != '0') {
	    action = (neg)? -1 : 1;
	} else {
	    action = (neg)? 1 : -1;
	}
    }

    if (action > 0) {
	state->flags |= flag;
    } else if (action < 0) {
	state->flags &= ~flag;
    }
}
