NYTP_write_process_start(NYTP_file ofile, U32 pid, U32 ppid,
                         NV time_of_day)
{
    size_t total;
    size_t retval;

    total = retval = output_tag_u32(ofile, NYTP_TAG_PID_START, pid);
    if (retval < 1)
        return retval;

    total += retval = output_u32(ofile, ppid);
    if (retval < 1)
        return retval;

    total += retval = output_nv(ofile, time_of_day);
    if (retval < 1)
        return retval;

    return total;
}
