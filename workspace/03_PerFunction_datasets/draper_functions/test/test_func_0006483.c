print_progress(struct undup *und, int final)
{
    double t = rtc();

    if (final || t > und->lastprint + 1) {
        u64 numblock = und->backblocks + und->datablocks;

        fprintf(stderr, "\r %lld MiB -> %lld MiB %.1f MiB/s %.1f%% backref %.1f%% data",
                (long long)und->logoff / 1024 / 1024,
                (long long)und->outpos / 1024 / 1024,
                und->logoff / (t - und->start) / 1024 / 1024,
                und->backblocks * 100. / numblock,
                und->datablocks * 100. / numblock);
        und->lastprint = t;
    }
}
