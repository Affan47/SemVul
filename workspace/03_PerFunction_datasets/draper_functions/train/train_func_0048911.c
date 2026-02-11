file_can_expand (const char *uri)
{
    const char *path;
    struct stat buf;
    char decoded_uri[1024];

    decode_uri (uri, decoded_uri, 1020);


    if (strncmp (decoded_uri, "file:", 5))  return 0.0;


    path = &decoded_uri[5];
    if (!*path)  return 0.0;


    if (lstat(path, &buf))  return 0.0;
    if (!S_ISDIR(buf.st_mode))  return 0.0;

    return 1.0;
}
