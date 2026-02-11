cleanup(CleanupStage)
{
#if CLICK_USERLEVEL
    if (_outfile)
	fclose(_outfile);
    _outfile = 0;
#endif
}
