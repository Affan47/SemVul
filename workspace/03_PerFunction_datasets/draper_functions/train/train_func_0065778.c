S_init_ids(pTHX)
{


#if !NO_TAINT_SUPPORT
    dVAR;
    const UV my_uid = PerlProc_getuid();
    const UV my_euid = PerlProc_geteuid();
    const UV my_gid = PerlProc_getgid();
    const UV my_egid = PerlProc_getegid();


    CHECK_MALLOC_TAINT(my_uid && (my_euid != my_uid || my_egid != my_gid));
    TAINTING_set( TAINTING_get | (my_uid && (my_euid != my_uid || my_egid != my_gid)) );
#endif


}
