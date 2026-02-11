netsys_sem_open(value namev,
			       value flagsv,
			       value modev,
			       value initv)
{
#ifdef HAVE_POSIX_SEM_NAMED
    sem_t *s;
    value r;
    unsigned int init;
    int flags;

    init = Long_val(initv);
    flags = convert_flag_list(flagsv, sem_open_flag_table);
    s = sem_open(String_val(namev),
		 flags,
		 Int_val(modev),
		 init);
    if (s == (sem_t *) SEM_FAILED) uerror("sem_open", namev);
    r = alloc_sem_block(s, 1);
    return r;
#else
    invalid_argument("Netsys.sem_open not available");
#endif
}
