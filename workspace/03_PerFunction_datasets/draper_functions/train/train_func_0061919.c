canvas_start_dsp(void)
{
    t_canvas *x;
    if (canvas_dspstate) ugen_stop();
    else sys_gui("pdtk_pd_dsp ON\n");
    ugen_start();

    for (x = canvas_list; x; x = x->gl_next)
        canvas_dodsp(x, 1, 0);

    canvas_dspstate = 1;
}
