PanStartStroke(void *data, DXMouseEvent *event)
{
    PanData pdata = (PanData)data;


    int b = WHICH_BUTTON(event);
    if (b != NO_BUTTON)
    {
        pdata->buttonPositions[b].x = event->x;
        pdata->buttonPositions[b].y = event->y;
    }
    return;
}
