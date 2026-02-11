snd_xform(sound_type snd,
                      rate_type sr,
                      time_type time,
                      time_type start_time,
                      time_type stop_time,
                      promoted_sample_type scale)
{
    long start_cnt, stop_cnt;


    if (start_time == MIN_START_TIME) {
        start_cnt = 0;
    } else {
        double new_start_cnt = ((start_time - time) * sr) + 0.5;
        start_cnt = ((new_start_cnt > 0) ? (long) new_start_cnt : 0);
    }


    if (stop_time == MAX_STOP_TIME) {
        stop_cnt = MAX_STOP;
    } else {
        double new_stop_cnt = ((stop_time - time) * sr) + 0.5;
        if (new_stop_cnt < MAX_STOP) {
            stop_cnt = (long) new_stop_cnt;
        } else {
            errputstr("Warning: stop count overflow in snd_xform\n");
            stop_cnt = MAX_STOP;
        }
    }

    if (stop_cnt > snd->stop) {
        stop_cnt = snd->stop;
    }

    if (stop_cnt < 0 || start_cnt >= stop_cnt) {
        snd = sound_create(NULL, time, sr, 1.0);


        ffree_snd_list(snd->list, "snd_xform");
        snd->list = zero_snd_list;
        nyquist_printf("snd_xform: (stop_time < t0 or start >= stop) "
                       "-> zero sound = %p\n", snd);

    } else {
        snd = sound_copy(snd);
        snd->t0 = time;
        if (start_cnt) {
            snd->current -= start_cnt;


            if ((snd->get_next != SND_get_first) &&
                (snd->get_next != SND_flush)) {
                errputstr("snd_xform: SND_get_first expected\n");
                EXIT(1);
            }

            snd->get_next = SND_flush;
            stop_cnt -= start_cnt;
        }
        snd->stop = stop_cnt;
        snd->sr = sr;
        snd->scale *= (float) scale;
    }
    return snd;
}
