scrollbar_reset(void)
{
    D_SCROLLBAR(("scrollbar_reset()\n"));
    last_top = last_bot = 0;
    scrollbar.init = 0;
}
