cmp_func(const file_info * file1, const file_info * file2)
{
    if (file1->ino < file2->ino)
        return -1;

    if (file1->ino > file2->ino)
        return 1;

    if (file1->dev < file2->dev)
        return -1;

    return file1->dev > file2->dev;
}
