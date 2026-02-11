acquire_socket_lock(const std::string &sock_name, std::string *out_lockfile_name)
{
    bool success = false;
    std::string lockfile;
    lockfile.reserve(sock_name.size() + strlen(LOCKPOSTFIX));
    lockfile = sock_name;
    lockfile.append(LOCKPOSTFIX);
    if (acquire_lock_file(lockfile, LOCKTIMEOUT, 1))
    {
        out_lockfile_name->swap(lockfile);
        success = true;
    }
    return success;
}
