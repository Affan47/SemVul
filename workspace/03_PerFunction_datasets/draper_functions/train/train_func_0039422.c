ff_pretty_time2(double time,
        ft_ull * ret_pretty_time1, char const ** ret_pretty_label1,
        ft_ull * ret_pretty_time2, char const ** ret_pretty_label2)
{
    ft_size i = 0;
    for (; i < fc_pretty_time_len - 1; i++) {
        if (time < fc_pretty_time[i+1])
            break;
    }
    double time1 = time / fc_pretty_time[i];

    * ret_pretty_time1 = ff_pretty_number(time1);
    * ret_pretty_label1 = fc_pretty_time_unit[i];
    if (ret_pretty_time2 == NULL || ret_pretty_label2 == NULL)
        return;

    * ret_pretty_time2 = 0;
    * ret_pretty_label2 = NULL;

    if (i == 0 || time1 <= 1.0 || time1 > 1.9)
        return;

    time -= (ft_ull) time1 * fc_pretty_time[i];
    if (time <= 0.0)
        return;

    ft_size j = 0;
    for (j = 0; j < fc_pretty_time_len - 1; j++) {
        if (time < fc_pretty_time[j+1])
            break;
    }
    if (j + 1 == i) {
        * ret_pretty_time1 = 1;
        * ret_pretty_time2 = ff_pretty_number(time / fc_pretty_time[j]);
        * ret_pretty_label2 = fc_pretty_time_unit[j];
    }
}
