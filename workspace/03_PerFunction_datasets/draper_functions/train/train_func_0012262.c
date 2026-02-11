glusterd_friend_sm_inject_event (glusterd_friend_sm_event_t *event)
{
        GF_ASSERT (event);
        gf_log ("glusterd", GF_LOG_DEBUG, "Enqueue event: '%s'",
                glusterd_friend_sm_event_name_get (event->event));
        list_add_tail (&event->list, &gd_friend_sm_queue);

        return 0;
}
