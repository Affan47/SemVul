write_ints(int fd, Bit32u *buffer, size_t count)
{
    int res;
    size_t i;
    Bit32u *p;

    for (p = buffer, i=0; i<count; p++, i++)
      *p=htod32(*p);

    res=::write(fd, (void*)buffer, count * 4);

    for (p = buffer, i=0; i<count; p++, i++)
      *p=dtoh32(*p);

    return res;
}
