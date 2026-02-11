operator=(const OFFilename &arg)
{
    if (&arg != this)
    {
        free(filename_);
        filename_ = (arg.filename_ != NULL) ? strdup(arg.filename_) : NULL;
#if (defined(WIDE_CHAR_FILE_IO_FUNCTIONS) || defined(WIDE_CHAR_MAIN_FUNCTION)) && defined(_WIN32)
        free(wfilename_);
        wfilename_ = (arg.wfilename_ != NULL) ? _wcsdup(arg.wfilename_) : NULL;
#endif
    }
    return *this;
}
