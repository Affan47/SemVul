get_my_path(char *exe, size_t maxLen)
{
    char proc[64];
    snprintf(proc, sizeof proc, "/proc/%d/exe", getpid());
    int err = readlink(proc, exe, maxLen - 1);
    if(err > 0) {
        exe[err] = '\0';
    } else {
        exe[0] = '\0';
    }
}
