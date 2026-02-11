encoder_progress( lame_global_flags const* gf )
{
    if (silent <= 0) {
        int const frames = lame_get_frameNum(gf);
        if (update_interval <= 0) {
            if ((frames % 100) != 0) {
                return;
            }
        }
        else {
            static double last_time = 0.0;
            if (frames != 0 && frames != 9) {
                double const act = GetRealTime();
                double const dif = act - last_time;
                if (dif >= 0 && dif < update_interval) {
                    return;
                }
            }
            last_time = GetRealTime();
        }
#ifdef BRHIST
        if (brhist) {
            brhist_jump_back();
        }
#endif
        timestatus(gf);
#ifdef BRHIST
        if (brhist) {
            brhist_disp(gf);
        }
#endif
        console_flush();
    }
}
