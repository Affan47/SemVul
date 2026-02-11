gf_proc_dump_pending_frames_to_dict (call_pool_t *call_pool, dict_t *dict)
{
        int             ret = -1;
        call_stack_t    *trav = NULL;
        char            key[GF_DUMP_MAX_BUF_LEN] = {0,};
        int             i = 0;

        if (!call_pool || !dict)
                return;

        ret = TRY_LOCK (&call_pool->lock);
        if (ret) {
                gf_log (THIS->name, GF_LOG_WARNING, "Unable to dump call pool"
                        " to dict. errno: %d", errno);
                return;
        }

        ret = dict_set_int32 (dict, "callpool.count", call_pool->cnt);
        if (ret)
                goto out;

        list_for_each_entry (trav, &call_pool->all_frames, all_frames) {
                memset (key, 0, sizeof (key));
                snprintf (key, sizeof (key), "callpool.stack%d", i);
                gf_proc_dump_call_stack_to_dict (trav, key, dict);
                i++;
        }

out:
        UNLOCK (&call_pool->lock);

        return;
}
