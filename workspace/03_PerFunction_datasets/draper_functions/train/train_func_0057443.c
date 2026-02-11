av_filename_number_test(const char *filename)
{
    char buf[1024];
    return filename && (av_get_frame_filename(buf, sizeof(buf), filename, 1)>=0);
}
