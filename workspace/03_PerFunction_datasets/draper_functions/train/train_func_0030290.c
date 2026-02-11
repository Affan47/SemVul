t4_tx_init(t4_state_t *s, const char *file, int start_page, int stop_page)
{
    int run_space;

    memset(s, 0, sizeof(*s));
    span_log_init(&s->logging, SPAN_LOG_NONE, NULL);
    span_log_set_protocol(&s->logging, "T.4");
    s->rx = FALSE;

    span_log(&s->logging, SPAN_LOG_FLOW, "Start tx document\n");

    if (open_tiff_input_file(s, file) < 0)
        return NULL;
    s->file = strdup(file);
    s->start_page = (start_page >= 0)  ?  start_page  :  0;
    s->stop_page = (stop_page >= 0)  ?  stop_page : INT_MAX;

    if (get_tiff_directory_info(s))
    {
        close_tiff_input_file(s);
        return NULL;
    }

    s->rows_to_next_1d_row = s->max_rows_to_next_1d_row - 1;

    s->pages_transferred = s->start_page;
    s->pages_in_file = -1;

    run_space = (s->image_width + 4)*sizeof(uint32_t);
    if ((s->cur_runs = (uint32_t *) malloc(run_space)) == NULL)
        return NULL;
    if ((s->ref_runs = (uint32_t *) malloc(run_space)) == NULL)
    {
        free_buffers(s);
        close_tiff_input_file(s);
        return NULL;
    }
    if ((s->row_buf = malloc(s->bytes_per_row)) == NULL)
    {
        free_buffers(s);
        close_tiff_input_file(s);
        return NULL;
    }
    s->ref_runs[0] =
    s->ref_runs[1] =
    s->ref_runs[2] =
    s->ref_runs[3] = s->image_width;
    s->ref_steps = 1;
    s->image_buffer_size = 0;
    return s;
}
