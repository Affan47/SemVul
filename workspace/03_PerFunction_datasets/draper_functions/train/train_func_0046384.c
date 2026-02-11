gf_timer_call_after (glusterfs_ctx_t *ctx,
                     struct timeval delta,
                     gf_timer_cbk_t callbk,
                     void *data)
{
        gf_timer_registry_t *reg = NULL;
        gf_timer_t *event = NULL;
        gf_timer_t *trav = NULL;
        unsigned long long at = 0L;

        if (ctx == NULL)
        {
                gf_log_callingfn ("timer", GF_LOG_ERROR, "invalid argument");
                return NULL;
        }

        reg = gf_timer_registry_init (ctx);

        if (!reg) {
                gf_log_callingfn ("timer", GF_LOG_ERROR, "!reg");
                return NULL;
        }

        event = GF_CALLOC (1, sizeof (*event), gf_common_mt_gf_timer_t);
        if (!event) {
                return NULL;
        }
        gettimeofday (&event->at, NULL);
        event->at.tv_usec = ((event->at.tv_usec + delta.tv_usec) % 1000000);
        event->at.tv_sec += ((event->at.tv_usec + delta.tv_usec) / 1000000);
        event->at.tv_sec += delta.tv_sec;
        at = TS (event->at);
        event->callbk = callbk;
        event->data = data;
        event->xl = THIS;
        pthread_mutex_lock (&reg->lock);
        {
                trav = reg->active.prev;
                while (trav != &reg->active) {
                        if (TS (trav->at) < at)
                                break;
                        trav = trav->prev;
                }
                event->prev = trav;
                event->next = event->prev->next;
                event->prev->next = event;
                event->next->prev = event;
        }
        pthread_mutex_unlock (&reg->lock);
        return event;
}
