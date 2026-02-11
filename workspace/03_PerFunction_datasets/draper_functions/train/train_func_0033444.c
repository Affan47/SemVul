write_base(user_interaction & dialog, const string & filename, const database *base, bool overwrite)
{
    thread_cancellation thr;
    database_dump_options dat_opt;

    dat_opt.set_overwrite(overwrite);
    thr.block_delayed_cancellation(true);
    base->dump(dialog, filename, dat_opt);
    thr.block_delayed_cancellation(false);
}
