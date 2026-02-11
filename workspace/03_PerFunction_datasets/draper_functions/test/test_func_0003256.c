icaldurationtype_from_int(int t)
{
        struct icaldurationtype dur;
        int used = 0;

        dur = icaldurationtype_null_duration();

        if(t < 0){
            dur.is_neg = 1;
            t = -t;
        }

        dur.weeks = (t - used) / (60 * 60 * 24 * 7);
        used += dur.weeks * (60 * 60 * 24 * 7);
        dur.days = (t - used) / (60 * 60 * 24);
        used += dur.days * (60 * 60 * 24);
        dur.hours = (t - used) / (60 * 60);
        used += dur.hours * (60 * 60);
        dur.minutes = (t - used) / (60);
        used += dur.minutes * (60);
        dur.seconds = (t - used);

        return dur;
}
