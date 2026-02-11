write(const char* s, std::streamsize n)
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    DWORD ignore;
    if (!::WriteFile(handle_, s, n, &ignore, NULL))
        throw_system_failure("failed writing");
    return n;
#else
    int amt = BOOST_IOSTREAMS_FD_WRITE(handle_, s, n);
    if (amt < n)
        throw_system_failure("failed writing");
    return n;
#endif
}
