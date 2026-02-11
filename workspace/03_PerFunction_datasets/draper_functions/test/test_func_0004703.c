event_handler(input_module_t *mod, enum event_type ev, void *param)
{
    stdinpcm_state *s = mod->internal;

    switch(ev)
    {
        case EVENT_SHUTDOWN:
	    close_module(mod);
            break;
        case EVENT_NEXTTRACK:
            ((stdinpcm_state *)mod->internal)->newtrack = 1;
            break;
        case EVENT_METADATAUPDATE:
            thread_mutex_lock(&s->metadatalock);
            if(s->metadata)
            {
                char **md = s->metadata;
                while(*md)
                    free(*md++);
                free(s->metadata);
            }

            s->metadata = (char **)param;
            s->newtrack = 1;
            thread_mutex_unlock(&s->metadatalock);
            break;
        default:
            LOG_WARN1("Unhandled event %d", ev);
            return -1;
    }

    return 0;
}
