DXLClearEvent(DXLEvent *event)
{
    if (event->contents && event->contents != event->buffer)
        free(event->contents);
    event->next = NULL;
    event->contentsSize = 0;
    event->buffer[0] = '\0';
    event->contents = event->buffer;
    return OK;
}
