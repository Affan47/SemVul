ctx_progress_start_func (GPContext __unused__ *context, float target,
                         const char *str, void *data)
{
	GPParams *p = data;
        unsigned int id, len;
        static unsigned char initialized = 0;

        if (!initialized) {
                memset (progress_states, 0, sizeof (progress_states));
                initialized = 1;
        }

	if (p->flags & FLAGS_QUIET)
		return 0;


        len = (p->cols * 0.5 < 4) ? 0 : MIN (p->cols * 0.5, MAX_MSG_LEN);


        for (id = 0; id < MAX_PROGRESS_STATES; id++)
                if (!progress_states[id].target)
                        break;
        if (id == MAX_PROGRESS_STATES)
                id--;
        progress_states[id].target = target;
        strncpy (progress_states[id].message, str, len + 1);
        progress_states[id].count = 0;
        progress_states[id].last.time = time (NULL);
        progress_states[id].last.current = progress_states[id].last.left = 0.;


        if (progress_states[id].message[len - 1]) {
                progress_states[id].message[len - 1] = '\0';
                progress_states[id].message[len - 2] = '.';
                progress_states[id].message[len - 3] = '.';
                progress_states[id].message[len - 4] = '.';
        }

        return (id);
}
