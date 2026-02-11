OPL_Queue_Push(opl_callback_queue_t *queue,
                    opl_callback_t callback, void *data,
                    unsigned int time)
{
    int entry_id;
    int parent_id;

    if (queue->num_entries >= MAX_OPL_QUEUE)
    {
        fprintf(stderr, "OPL_Queue_Push: Exceeded maximum callbacks\n");
        return;
    }


    entry_id = queue->num_entries;
    ++queue->num_entries;


    while (entry_id > 0)
    {
        parent_id = (entry_id - 1) / 2;


        if (time >= queue->entries[parent_id].time)
        {
            break;
        }


        memcpy(&queue->entries[entry_id],
               &queue->entries[parent_id],
               sizeof(opl_queue_entry_t));


        entry_id = parent_id;
    }


    queue->entries[entry_id].callback = callback;
    queue->entries[entry_id].data = data;
    queue->entries[entry_id].time = time;
}
