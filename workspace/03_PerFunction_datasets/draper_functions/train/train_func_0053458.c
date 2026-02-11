gdth_wait(gdth_ha_str *ha, int index, u32 time)
{
    int answer_found = FALSE;
    int wait_index = 0;

    TRACE(("gdth_wait() hanum %d index %d time %d\n", ha->hanum, index, time));

    if (index == 0)
        return 1;

    do {
	__gdth_interrupt(ha, true, &wait_index);
        if (wait_index == index) {
            answer_found = TRUE;
            break;
        }
        gdth_delay(1);
    } while (--time);

    while (gdth_test_busy(ha))
        gdth_delay(0);

    return (answer_found);
}
