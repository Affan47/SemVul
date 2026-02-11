StringRead(FILE16 *file, unsigned char *buf, int max_count)
{
    char *p = (char *)file->handle + file->handle2;

    if(file->handle3 >= 0 && file->handle2 + max_count > file->handle3)
	max_count = file->handle3 - file->handle2;

    if(max_count <= 0)
	return 0;

    memcpy(buf, p, max_count);
    file->handle2 += max_count;

    return max_count;
}
