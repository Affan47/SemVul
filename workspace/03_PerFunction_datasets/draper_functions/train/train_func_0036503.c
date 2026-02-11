my_numbox_key(void *z, t_floatarg fkey)
{
    t_my_numbox *x = z;
    char c=fkey;
    char buf[3];
    buf[1] = 0;

    if (c == 0)
    {
        x->x_gui.x_fsf.x_change = 0;
        clock_unset(x->x_clock_reset);
        sys_queuegui(x, x->x_gui.x_glist, my_numbox_draw_update);
        return;
    }
    if(((c>='0')&&(c<='9'))||(c=='.')||(c=='-')||
        (c=='e')||(c=='+')||(c=='E'))
    {
        if(strlen(x->x_buf) < (IEMGUI_MAX_NUM_LEN-2))
        {
            buf[0] = c;
            strcat(x->x_buf, buf);
            sys_queuegui(x, x->x_gui.x_glist, my_numbox_draw_update);
        }
    }
    else if((c=='\b')||(c==127))
    {
        int sl=strlen(x->x_buf)-1;

        if(sl < 0)
            sl = 0;
        x->x_buf[sl] = 0;
        sys_queuegui(x, x->x_gui.x_glist, my_numbox_draw_update);
    }
    else if((c=='\n')||(c==13))
    {
        x->x_val = atof(x->x_buf);
        x->x_buf[0] = 0;
        x->x_gui.x_fsf.x_change = 0;
        clock_unset(x->x_clock_reset);
        my_numbox_clip(x);
        my_numbox_bang(x);
        sys_queuegui(x, x->x_gui.x_glist, my_numbox_draw_update);
    }
    clock_delay(x->x_clock_reset, 3000);
}
