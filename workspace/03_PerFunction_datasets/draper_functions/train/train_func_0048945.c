netsys_mem_send(value fdv, value memv, value offv, value lenv,
			       value flagsv)
{
    intnat numbytes;
    intnat ret;
    char *data;
    int flags;
#ifdef _WIN32
    DWORD err = 0;
    SOCKET s;
#else
    int s;
#endif

    numbytes = Long_val(lenv);
    data = ((char *) (Bigarray_val(memv)->data)) + Long_val(offv);
    flags = convert_flag_list(flagsv, msg_flag_table);

#ifdef _WIN32
    s = Socket_val(fdv);
#else
    s = Int_val(fdv);
#endif

    enter_blocking_section();
    ret = send(s, data, (int) numbytes, flags);

#ifdef _WIN32
    if (ret == -1) err = WSAGetLastError();
    leave_blocking_section();
    if (ret == -1) win32_maperr(err);
#else
    leave_blocking_section();
#endif

    if (ret == -1) uerror("mem_send", Nothing);
    return Val_long(ret);
}
