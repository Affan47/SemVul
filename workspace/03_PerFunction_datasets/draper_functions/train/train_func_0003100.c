procescounter(int *counter, const char *text, int speed, int keys,
              int lastkeys, int down, int up, int tenskip, int min,
              int max)
{
    static int pid = -1;
    int changed = 0;
    char str[80];
    if (tl_lookup_timer(arrowtimer) > 1000000)
        tl_reset_timer(arrowtimer);
    if ((keys & up) && !(lastkeys & up)) {
        (*counter)++;
        tenskip = 0;
        changed = 1;
        tl_reset_timer(arrowtimer);
    }
    if ((keys & down) && !(lastkeys & down)) {
        (*counter)--;
        tenskip = 0;
        changed = 1;
        tl_reset_timer(arrowtimer);
    }
    while (tl_lookup_timer(arrowtimer) > speed * FRAMETIME) {
        tl_slowdown_timer(arrowtimer, speed * FRAMETIME);
        if (keys & up) {
            if (tenskip && !(*counter % 10))
                (*counter) += 10;
            else
                (*counter)++;
            changed = 1;
        }
        if (keys & down) {
            if (tenskip && !(*counter % 10))
                (*counter) -= 10;
            else
                (*counter)--;
            changed = 1;
        }
    }
    if (changed) {
        if (*counter > max)
            *counter = max;
        if (*counter < min)
            *counter = min;
        sprintf(str, text, *counter);
        uih_rmmessage(uih, pid);
        pid = uih_message(uih, str);
        ui_flush();
    }
    return changed;
}
