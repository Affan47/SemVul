read(char* s, std::streamsize n)
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    DWORD result;
    if (!::ReadFile(handle_, s, n, &result, NULL))
    {

        if (GetLastError() == ERROR_BROKEN_PIPE)
        {
            result = 0;
        }
        else
            throw_system_failure("failed reading");
    }
    return result == 0 ? -1 : static_cast<std::streamsize>(result);
#else
    errno = 0;
    std::streamsize result = BOOST_IOSTREAMS_FD_READ(handle_, s, n);
    if (errno != 0)
        throw_system_failure("failed reading");
    return result == 0 ? -1 : result;
#endif
}
