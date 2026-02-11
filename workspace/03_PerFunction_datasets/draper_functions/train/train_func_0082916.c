NYTP_write_process_end(NYTP_file ofile, U32 pid, NV time_of_day)
{
    size_t total;
    size_t retval;

    total = retval = output_tag_u32(ofile, NYTP_TAG_PID_END, pid);
    if (retval < 1)
        return retval;

    total += retval = output_nv(ofile, time_of_day);
    if (retval < 1)
        return retval;

    return total;
}
