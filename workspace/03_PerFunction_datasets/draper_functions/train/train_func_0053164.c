init_io_self_test(const fr_args & args)
{
    int err;
    if ((err = pre_init_io()) == 0) {

        FT_IO_NS fr_io_self_test * io = new FT_IO_NS fr_io_self_test(* this_persist);

        if ((err = io->open(args)) == 0)
            post_init_io(io);
        else
            delete io;
    }
    return err;
}
