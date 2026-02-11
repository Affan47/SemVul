bkn_proc_rate_write(struct file *file, const char *buf,
                   size_t count, loff_t *loff)
{
    bkn_switch_info_t *sinfo;
    char rate_str[40];
    char *ptr;
    int unit, chan;

    if (count >= sizeof(rate_str)) {
        count = sizeof(rate_str) - 1;
    }
    if (copy_from_user(rate_str, buf, count)) {
        return -EFAULT;
    }

    unit = simple_strtol(rate_str, NULL, 10);
    sinfo = bkn_sinfo_from_unit(unit);
    if (sinfo == NULL) {
        gprintk("Warning: unknown unit\n");
        return count;
    }


    if ((ptr = strstr(rate_str, "rx_rate=")) != NULL) {
        ptr += 7;
        chan = 0;
        do {
            ptr++;
            sinfo->rx[chan].rate_max = simple_strtol(ptr, NULL, 10);
        }
        while ((ptr = strchr(ptr, ',')) != NULL && ++chan < NUM_RX_CHAN);
        bkn_rx_rate_config(sinfo);
    } else  if ((ptr = strstr(rate_str, "rx_burst=")) != NULL) {
        ptr += 8;
        chan = 0;
        do {
            ptr++;
            sinfo->rx[chan].burst_max = simple_strtol(ptr, NULL, 10);
        }
        while ((ptr = strchr(ptr, ',')) != NULL && ++chan < NUM_RX_CHAN);
        bkn_rx_rate_config(sinfo);
    } else {
        gprintk("Warning: unknown configuration setting\n");
    }

    return count;
}
