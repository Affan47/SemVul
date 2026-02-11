is_id3v1 (FILE * fp)
{
    int n=0;
    char buf[16];
    size_t savedFilePosition;

    savedFilePosition = ftell (fp);
    fseek (fp, 0, SEEK_END);
    do {
        n++;
        memset (buf, 0, sizeof (buf));
        fseek (fp, ((-128)*n) - 3 , SEEK_END);
        if (fread (&buf, 1, sizeof (buf), fp) != sizeof (buf))
        {
            fseek (fp, savedFilePosition, SEEK_SET);
            return 0;
        }
        if (memcmp (buf, "APETAGEX",8) == 0)
        break;
    } while (memcmp (buf+3, "TAG", 3) == 0);

    fseek (fp, savedFilePosition, SEEK_SET);
    return (n-1)*128;
}
