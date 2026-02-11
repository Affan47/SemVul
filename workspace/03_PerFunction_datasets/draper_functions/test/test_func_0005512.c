length_base_file_name(tiffsep_device * pdev)
{
    int base_filename_length = strlen(pdev->fname);

#define REMOVE_TIF_FROM_BASENAME 1
#if REMOVE_TIF_FROM_BASENAME
    if (base_filename_length > 4 &&
        pdev->fname[base_filename_length - 4] == '.'  &&
        toupper(pdev->fname[base_filename_length - 3]) == 'T'  &&
        toupper(pdev->fname[base_filename_length - 2]) == 'I'  &&
        toupper(pdev->fname[base_filename_length - 1]) == 'F')
        base_filename_length -= 4;
#endif
#undef REMOVE_TIF_FROM_BASENAME

    return base_filename_length;
}
