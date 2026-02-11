getServerStatus(const char* fileName, fxStr& status)
{
    int fd = Sys::open(fileName, O_RDONLY);
    if (fd > 0) {
        struct stat sb;
        (void) Sys::fstat(fd, sb);
        status.resize((u_int) sb.st_size);
        char* buff = new char[sb.st_size];
        int n = Sys::read(fd, buff, (size_t) sb.st_size);
        status = buff;
        Sys::close(fd);
        if (n > 0 && status[n-1] == '\n') n--;
        if (n == 0) {
            status = "No status (empty file)";
        } else {
            status.resize(n);
        }
        delete [] buff;
    } else {
        status = "No status (cannot open file)";
    }
}
