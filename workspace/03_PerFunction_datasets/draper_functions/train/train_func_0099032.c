FreeWild(count, files)
    int	    count;
    char_u  **files;
{
    if (count <= 0 || files == NULL)
	return;
#if defined(__EMX__) && defined(__ALWAYS_HAS_TRAILING_NULL_POINTER)


    _fnexplodefree((char **)files);
#else
    while (count--)
	vim_free(files[count]);
    vim_free(files);
#endif
}
