event_win_is_mywin(register event_dispatcher_data_t *data, Window win)
{

    register unsigned short i;

    ASSERT_RVAL(data != NULL, 0);

    for (i = 0; i < data->num_my_windows; i++) {
        if (data->my_windows[i] == win) {
            return 1;
        }
    }
    return 0;
}
