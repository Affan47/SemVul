_dxf_ExLogClose()
{
    if (lfd != -1)
    {
	close (lfd);
	if (lfp != NULL)
	    fclose (lfp);
    }
}
