add_entry(pTHX_ AV *dest_av, unsigned int file_num, unsigned int line_num,
NV time, unsigned int eval_file_num, unsigned int eval_line_num, int count)
{

    unsigned int fid = (eval_line_num) ? eval_file_num : file_num;
    SV *line_time_rvav = *av_fetch(dest_av, fid, 1);

    if (!SvROK(line_time_rvav))
        sv_setsv(line_time_rvav, newRV_noinc((SV*)newAV()));

    store_profile_line_entry(aTHX_ line_time_rvav, line_num, time, count, fid);
}
