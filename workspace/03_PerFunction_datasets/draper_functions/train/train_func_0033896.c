input_get_default_joystick (struct uae_input_device *uid, int num, int port, int af, int mode, bool gp)
{
    int h,v;
    unsigned int j;
    struct didata *did;


    write_log("input_get_default_joystick num=%d port=%d af=%d mode=%d\n", num, port, af, mode);


    if (mode == JSEM_MODE_MOUSE_CDTV) {
        h = INPUTEVENT_MOUSE_CDTV_HORIZ;
        v = INPUTEVENT_MOUSE_CDTV_VERT;
    } else if (port >= 2) {
        h = port == 3 ? INPUTEVENT_PAR_JOY2_HORIZ : INPUTEVENT_PAR_JOY1_HORIZ;
        v = port == 3 ? INPUTEVENT_PAR_JOY2_VERT : INPUTEVENT_PAR_JOY1_VERT;
    } else {
        h = port ? INPUTEVENT_JOY2_HORIZ : INPUTEVENT_JOY1_HORIZ;;
        v = port ? INPUTEVENT_JOY2_VERT : INPUTEVENT_JOY1_VERT;
    }
    setid (uid, num, ID_AXIS_OFFSET + 0, 0, port, h);
    setid (uid, num, ID_AXIS_OFFSET + 1, 0, port, v);

    if (port >= 2) {
        setid_af (uid, num, ID_BUTTON_OFFSET + 0, 0, port, port == 3 ? INPUTEVENT_PAR_JOY2_FIRE_BUTTON : INPUTEVENT_PAR_JOY1_FIRE_BUTTON, af);
    } else {
        setid_af (uid, num, ID_BUTTON_OFFSET + 0, 0, port, port ? INPUTEVENT_JOY2_FIRE_BUTTON : INPUTEVENT_JOY1_FIRE_BUTTON, af);
        setid (uid, num, ID_BUTTON_OFFSET + 1, 0, port, port ? INPUTEVENT_JOY2_2ND_BUTTON : INPUTEVENT_JOY1_2ND_BUTTON);
        setid (uid, num, ID_BUTTON_OFFSET + 2, 0, port, port ? INPUTEVENT_JOY2_3RD_BUTTON : INPUTEVENT_JOY1_3RD_BUTTON);
    }

    if (mode == JSEM_MODE_JOYSTICK_CD32) {
        setid_af (uid, num, ID_BUTTON_OFFSET + 0, 0, port, port ? INPUTEVENT_JOY2_CD32_RED : INPUTEVENT_JOY1_CD32_RED, af);
        setid_af (uid, num, ID_BUTTON_OFFSET + 0, 1, port, port ? INPUTEVENT_JOY2_FIRE_BUTTON : INPUTEVENT_JOY1_FIRE_BUTTON, af);
        setid (uid, num, ID_BUTTON_OFFSET + 1, 0, port, port ? INPUTEVENT_JOY2_CD32_BLUE : INPUTEVENT_JOY1_CD32_BLUE);
        setid (uid, num, ID_BUTTON_OFFSET + 1, 1, port,  port ? INPUTEVENT_JOY2_2ND_BUTTON : INPUTEVENT_JOY1_2ND_BUTTON);
        setid (uid, num, ID_BUTTON_OFFSET + 2, 0, port, port ? INPUTEVENT_JOY2_CD32_GREEN : INPUTEVENT_JOY1_CD32_GREEN);
        setid (uid, num, ID_BUTTON_OFFSET + 3, 0, port, port ? INPUTEVENT_JOY2_CD32_YELLOW : INPUTEVENT_JOY1_CD32_YELLOW);
        setid (uid, num, ID_BUTTON_OFFSET + 4, 0, port, port ? INPUTEVENT_JOY2_CD32_RWD : INPUTEVENT_JOY1_CD32_RWD);
        setid (uid, num, ID_BUTTON_OFFSET + 5, 0, port, port ? INPUTEVENT_JOY2_CD32_FFW : INPUTEVENT_JOY1_CD32_FFW);
        setid (uid, num, ID_BUTTON_OFFSET + 6, 0, port, port ? INPUTEVENT_JOY2_CD32_PLAY :  INPUTEVENT_JOY1_CD32_PLAY);
    }
    if (num == 0) {
        return 1;
    }
    return 0;
}
