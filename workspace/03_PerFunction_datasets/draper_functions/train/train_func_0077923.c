printfilever(int32 file_id)
{
    uint32 major, minor, release;
    char string[LIBVSTR_LEN+1];

    if (Hgetfileversion(file_id, &major, &minor, &release, string) == SUCCEED)
      {
        string[LIBVSTR_LEN] = '\0';
        printf("Last modified with %s\n\n", string);
      }
    else
        printf("(Has no library version information)\n\n");
}
