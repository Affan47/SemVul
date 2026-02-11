mode_string(int mode)
{
    static char     buffer[11];

    buffer[0] = '?';
    switch (mode & S_IFMT)
    {
    case S_IFDIR: buffer[0] = 'd'; break;
    case S_IFREG: buffer[0] = '-'; break;
    case S_IFLNK: buffer[0] = 'l'; break;
    }
    buffer[1] = (mode & 0400) ? 'r' : '-';
    buffer[2] = (mode & 0200) ? 'w' : '-';
    buffer[3] = "-xSs"[((mode >> 6) & 1) | ((mode >> 10) & 2)];
    buffer[4] = (mode & 0040) ? 'r' : '-';
    buffer[5] = (mode & 0020) ? 'w' : '-';
    buffer[6] = "-xSs"[((mode >> 3) & 1) | ((mode >> 9) & 2)];
    buffer[7] = (mode & 0004) ? 'r' : '-';
    buffer[8] = (mode & 0002) ? 'w' : '-';
    buffer[9] = "-xTt"[(mode & 1) | ((mode >> 8) & 2)];
    buffer[10] = 0;
    return buffer;
}
