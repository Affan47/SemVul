fifo_end (output_plugin *p)
{
    if(p->flags & CONFIG_VERBOSE)
       plog("Closing FIFO file\n");
    fclose((FILE *)p->data);

    p->data = NULL;
    p->path = NULL;
    return 0;
}
