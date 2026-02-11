compute_real_filename(char *filename, int max_size)
{
    char file1[1024];
    char file2[1024];
    char *p;
    FFStream *stream;


    av_strlcpy(file1, filename, sizeof(file1));
    p = strrchr(file1, '.');
    if (p)
        *p = '\0';
    for(stream = first_stream; stream != NULL; stream = stream->next) {
        av_strlcpy(file2, stream->filename, sizeof(file2));
        p = strrchr(file2, '.');
        if (p)
            *p = '\0';
        if (!strcmp(file1, file2)) {
            av_strlcpy(filename, stream->filename, max_size);
            break;
        }
    }
}
