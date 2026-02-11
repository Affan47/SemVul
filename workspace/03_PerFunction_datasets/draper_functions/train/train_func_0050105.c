parser_run(struct parser_obj *po)
{
    int error = EOK;
    struct collection_item *item = NULL;
    uint32_t action = 0;
    action_fn operations[] = { parser_read,
                               parser_inspect,
                               parser_post,
                               parser_error,
                               NULL };

    TRACE_FLOW_ENTRY();

    while(1) {

        item = NULL;
        error = col_dequeue_item(po->queue, &item);
        if (error) {
            TRACE_ERROR_NUMBER("Failed to get action", error);
            return error;
        }


        action = *((uint32_t *)(col_get_item_data(item)));
        col_delete_item(item);

        if (action == PARSE_DONE) {

            TRACE_INFO_NUMBER("We are done", error);


            if ((po->ret == 0) &&
                (po->merge_error != 0) &&
                ((po->collision_flags & INI_MV1S_DETECT) ||
                 (po->collision_flags & INI_MV2S_DETECT) ||
                 (po->collision_flags & INI_MS_DETECT)))
                po->ret = po->merge_error;

            error = po->ret;
            break;
        }

        error = operations[action](po);
        if (error) {
            TRACE_ERROR_NUMBER("Failed to perform an action", error);
            return error;
        }

    }

    TRACE_FLOW_EXIT();
    return error;
}
