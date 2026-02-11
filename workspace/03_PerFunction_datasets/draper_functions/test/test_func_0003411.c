NYTP_write_new_fid(NYTP_file ofile, U32 id, U32 eval_fid,
                   U32 eval_line_num, U32 flags,
                   U32 size, U32 mtime,
                   const char *name, I32 len)
{
    size_t total;
    size_t retval;

    total = retval = output_tag_u32(ofile, NYTP_TAG_NEW_FID, id);
    if (retval < 1)
        return retval;

    total += retval = output_u32(ofile, eval_fid);
    if (retval < 1)
        return retval;

    total += retval = output_u32(ofile, eval_line_num);
    if (retval < 1)
        return retval;

    total += retval = output_u32(ofile, flags);
    if (retval < 1)
        return retval;

    total += retval = output_u32(ofile, size);
    if (retval < 1)
        return retval;

    total += retval = output_u32(ofile, mtime);
    if (retval < 1)
        return retval;

    total += retval = output_str(ofile, name, len);
    if (retval < 1)
        return retval;

    return total;
}
