ttfInterpreter__release(ttfInterpreter **ptti)
{
    ttfInterpreter *tti = *ptti;
    ttfMemory *mem = tti->ttf_memory;

    if(--tti->lock)
        return;
    mem->free(mem, tti->usage, "ttfInterpreter__release");
    mem->free(mem, tti->exec, "ttfInterpreter__release");
    mem->free(mem, *ptti, "ttfInterpreter__release");
    *ptti = 0;
}
