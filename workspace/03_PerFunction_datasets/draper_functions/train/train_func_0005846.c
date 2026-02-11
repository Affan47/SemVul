vis_runner_pass_audio (int time, float * data, int samples, int
 channels, int rate)
{
    pthread_mutex_lock (& mutex);

    if (! active)
        goto UNLOCK;


    if (current_node && current_node->channels != channels)
    {
        vis_node_free (current_node);
        current_node = NULL;
    }

    int at = 0;

    while (1)
    {
        if (! current_node)
        {
            int node_time = time;
            VisNode * last;


            if ((last = g_queue_peek_tail (& vis_list)))
                node_time = last->time + INTERVAL;

            at = channels * (int) ((int64_t) (node_time - time) * rate / 1000);

            if (at < 0)
                at = 0;
            if (at >= samples)
                break;

            current_node = g_malloc (sizeof (VisNode));
            current_node->time = node_time;
            current_node->data = g_malloc (sizeof (float) * channels * 512);
            current_node->channels = channels;
            current_frames = 0;
        }


        int copy = MIN (samples - at, channels * (512 - current_frames));
        memcpy (current_node->data + channels * current_frames, data + at, sizeof (float) * copy);
        current_frames += copy / channels;

        if (current_frames < 512)
            break;

        g_queue_push_tail (& vis_list, current_node);
        current_node = NULL;
    }

UNLOCK:
    pthread_mutex_unlock (& mutex);
}
