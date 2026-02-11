inungetc(int ch, INFILE * inpf)
{
    int result = ugly_inungetc(ch, inpf);

    if (inpf && (inpf->filepos))
    {
        update_wpos(inpf);
    }

    return (result);
}
