av_program_log_output(struct program *pr)
{
    int res;

    res = av_wait_prog(&pr->pri, 0, 1);
    if(res < 0)
        return res;

    if(res == 1)
        return 0;

    return 1;
}
