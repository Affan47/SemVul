is_ape (FILE * fp)
{
    char unsigned buf[32];
    size_t savedFilePosition;

    savedFilePosition = ftell (fp);
    memset (buf, 0, sizeof (buf));

    fseek (fp, (is_id3v1 (fp) ? -32 - 128 : -32), SEEK_END);
    if (fread (&buf, 1, sizeof (buf), fp) != sizeof (buf))
    {
        fseek (fp, savedFilePosition, SEEK_SET);
        return 0;
    }
    if (memcmp (buf, "APETAGEX", 8) != 0) {
        fseek (fp, savedFilePosition, SEEK_SET);
        return 0;
    }

    fseek (fp, savedFilePosition, SEEK_SET);

    return (int) (is_tag_ape2long (buf + 8 + 4) +
        (
            ( (is_tag_ape2long (buf + 8) == 2000) &&
            !(is_tag_ape2long (buf + 8 + 4 + 8) & IS_TAG_FOOTER_NOT)
            ) ? 32 : 0
        )
        );
}
