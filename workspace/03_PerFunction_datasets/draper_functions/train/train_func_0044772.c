recovercheckpoint(threadinfo *ti) {
    waituntilphase(REC_CKP);
    char path[256];
    sprintf(path, "%s/kvd-ckp-%" PRId64 "-%d",
            ckpdirs[ti->index() % ckpdirs.size()],
            ckp_gen.value(), ti->index());
    kvepoch_t gen = read_checkpoint(ti, path);
    always_assert(ckp_gen == gen);
    inactive();
}
