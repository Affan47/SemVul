_add_event_to_dict (circular_buffer_t *cb, void *data)
{
        int               ret = 0;
        shd_dump_t        *dump_data = NULL;
        shd_event_t       *shd_event = NULL;

        dump_data = data;
        shd_event = cb->data;
        if (shd_event->child != dump_data->child)
                goto out;
        ret = _add_path_to_dict (dump_data->this, dump_data->dict,
                                 dump_data->child, shd_event->path, &cb->tv,
                                 _gf_false);
out:
        return ret;
}
