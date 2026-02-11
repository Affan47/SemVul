save_typebuf()
{
    init_typebuf();
    saved_typebuf[curscript] = typebuf;

    if (alloc_typebuf() == FAIL)
    {
	closescript();
	return FAIL;
    }
    return OK;
}
