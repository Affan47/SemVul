print_power_on_pe(List *pwr_msg_list)
{
    int i, l = list_length(pwr_msg_list);

    fprintf(info_fp, "power_on_pe = {");

    for (i = 0; i < l; i++) {
        Power_msg *pmsg = (Power_msg *)list_nth_data(pwr_msg_list, i);

        if (!power_msg_is_sync_for_busy_wait(pmsg)) {
            int pe = power_msg_get_pwroff_pe(pmsg);
            fv_kind fv = power_msg_get_fv(pmsg);
            proc_kind pe_proc_kind = power_msg_get_pwroff_proc(pmsg);
            switch (pe_proc_kind) {
            case PROC_CPU:
                fprintf(info_fp, "CPU");
                break;
            case PROC_DTU:
                fprintf(info_fp, "DTU");
                break;
            case PROC_ACC:
                fprintf(info_fp, "ACC");
                break;
            default:
                fatal("Unknown proc_kind.\n");
            }
            if (power_msg_get_control_sync(pmsg) != NULL)
                fprintf(info_fp, "%d:%s(entry:%d)", pe, get_fv_str(fv),
                        power_msg_get_control_sync(pmsg)->entry);
            else
                fprintf(info_fp, "%d:%s", pe, get_fv_str(fv));

            if (i + 1 < l)
                fprintf(info_fp, ", ");
        }
    }
    fprintf(info_fp, "}");
}
