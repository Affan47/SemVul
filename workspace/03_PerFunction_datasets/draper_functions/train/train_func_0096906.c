ctrl_task_is_pwr_msg_sender(Ctrl_task *c, int sleep_id)
{
    List *li, *pwr_msg_list = ctrl_task_get_pwr_msg_list(c);

    for (li = pwr_msg_list; li != NULL; li = li->next) {
        Power_msg *m = li->data;

        if (power_msg_get_sleep_id(m) == sleep_id)
            return TRUE;
    }

    return FALSE;
}
