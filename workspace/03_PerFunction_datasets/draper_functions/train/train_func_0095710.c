hradio_float(t_hradio *x, t_floatarg f)
{
    int i=(int)f;

    if(i < 0)
        i = 0;
    if(i >= x->x_number)
        i = x->x_number-1;

    if (pd_class(&x->x_gui.x_obj.ob_pd) == hradio_old_class)
    {

        if((x->x_change)&&(i != x->x_on_old))
        {
            if(x->x_gui.x_fsf.x_put_in2out)
            {
                SETFLOAT(x->x_at, (t_float)x->x_on_old);
                SETFLOAT(x->x_at+1, 0.0);
                outlet_list(x->x_gui.x_obj.ob_outlet, &s_list, 2, x->x_at);
                if(x->x_gui.x_fsf.x_snd_able && x->x_gui.x_snd->s_thing)
                    pd_list(x->x_gui.x_snd->s_thing, &s_list, 2, x->x_at);
            }
        }
        if(x->x_on != x->x_on_old)
            x->x_on_old = x->x_on;
        x->x_on = i;
        (*x->x_gui.x_draw)(x, x->x_gui.x_glist, IEM_GUI_DRAW_MODE_UPDATE);
        x->x_on_old = x->x_on;
        if(x->x_gui.x_fsf.x_put_in2out)
        {
            SETFLOAT(x->x_at, (t_float)x->x_on);
            SETFLOAT(x->x_at+1, 1.0);
            outlet_list(x->x_gui.x_obj.ob_outlet, &s_list, 2, x->x_at);
            if(x->x_gui.x_fsf.x_snd_able && x->x_gui.x_snd->s_thing)
                pd_list(x->x_gui.x_snd->s_thing, &s_list, 2, x->x_at);
        }
    }
    else
    {
        x->x_on_old = x->x_on;
        x->x_on = i;
        (*x->x_gui.x_draw)(x, x->x_gui.x_glist, IEM_GUI_DRAW_MODE_UPDATE);
        if (x->x_gui.x_fsf.x_put_in2out)
        {
            outlet_float(x->x_gui.x_obj.ob_outlet, x->x_on);
            if(x->x_gui.x_fsf.x_snd_able && x->x_gui.x_snd->s_thing)
                pd_float(x->x_gui.x_snd->s_thing, x->x_on);
        }
    }
}
