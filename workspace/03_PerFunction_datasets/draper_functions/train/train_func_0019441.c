ui_updatestatus(void)
{
    double times =
        (uih->fcontext->currentformula->v.rr) / (uih->fcontext->s.rr);
    double timesnop = log(times) / log(10.0);
    double speed;
    uih_drawwindows(uih);
    driver->display();
    uih_cycling_continue(uih);
    speed = uih_displayed(uih);
    sprintf(statustext,
            gettext
            ("%s %.2f times (%.1fE) %2.2f frames/sec %c %i %i %i %i            "),
            times < 1 ? gettext("unzoomed") : gettext("zoomed"),
            times < 1 ? 1.0 / times : times, timesnop, speed,
            uih->autopilot ? 'A' : ' ', uih->fcontext->coloringmode + 1,
            uih->fcontext->incoloringmode + 1, uih->fcontext->plane + 1,
            uih->fcontext->maxiter);

    if (!(driver->flags & NOFLUSHDISPLAY))
        ui_flush();
    STAT(printf(gettext("framerate:%f\n"), speed));
    driver->print(0, 0, "");
}
