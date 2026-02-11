ui_mainloop(int loop)
{
    int inmovement = 1;
    int x, y, b, k;
    int time;
    driver->processevents((!inmovement && !uih->inanimation), &x, &y, &b,
                          &k);
    do {
        mousetype(uih->play ? REPLAYMOUSE : uih->
                  inhibittextoutput ? VJMOUSE : NORMALMOUSE);
        if (uih->display) {
            uih_prepare_image(uih);
            ui_updatestatus();
        }
        if ((time = tl_process_group(syncgroup, NULL)) != -1) {
            if (!inmovement && !uih->inanimation) {
                if (time > 1000000 / 50)
                    time = 1000000 / 50;
                if (time > delaytime) {
                    tl_sleep(time - delaytime);
                    tl_update_time();
                }
            }
            inmovement = 1;
        }
        if (delaytime || maxframerate) {
            tl_update_time();
            time = tl_lookup_timer(loopt);
            tl_reset_timer(loopt);
            time = 1000000 / maxframerate - time;
            if (time < delaytime)
                time = delaytime;
            if (time) {
                tl_sleep(time);
                tl_update_time();
            }
        }
        processbuffer();
        driver->processevents((!inmovement && !uih->inanimation), &x, &y,
                              &b, &k);

        inmovement = 0;
        ui_mouse(x, y, b, k);
        if (todriver)
            ui_driver(todriver - 1), todriver = 0;
        if (callresize)
            ui_resize(), callresize = 0;
    } while (loop);
}
