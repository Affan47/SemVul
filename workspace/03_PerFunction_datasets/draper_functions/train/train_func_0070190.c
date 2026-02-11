client_thread(void *data __attribute__ ((__unused__)))
{
    void *input_buffer = create_inputbuffer(&g_should_terminate);
    void *output_buffer = create_outputbuffer();

    while (!g_should_terminate) {
        int cc = queue_pop_connection();
        g_num_queued_connections--;
        g_num_active_connections++;
        if (cc >= 0) {
            if (g_debug_level >= 2)
                logger(LG_INFO, "Accepted client connection on fd %d", cc);
            set_inputbuffer_fd(input_buffer, cc);
            int keepalive = 1;
            unsigned requestnr = 1;
            while (keepalive) {
                if (g_debug_level >= 2 && requestnr > 1)
                    logger(LG_INFO, "Handling request %d on same connection", requestnr);
                keepalive = store_answer_request(input_buffer, output_buffer);
                flush_output_buffer(output_buffer, cc, &g_should_terminate);
                g_counters[COUNTER_REQUESTS]++;
                requestnr ++;
            }
            close(cc);
        }
        g_num_active_connections--;
    }
    delete_outputbuffer(output_buffer);
    delete_inputbuffer(input_buffer);
    return voidp;
}
