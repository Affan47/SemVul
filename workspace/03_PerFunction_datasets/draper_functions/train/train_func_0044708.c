jump(long position, int direction) {
    int offset = 0; if (direction <0) offset = -1;
    long npos = get_next_base(position,-direction) + offset;
    int swap;
    position += offset;
    swap = seq[position]; seq[position] = seq[npos]; seq[npos] = swap;
    return 0;
}
