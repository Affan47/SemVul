test(struct state *st, unsigned long int the_time, struct info *info, int pos[], int index)
{
    if (index == 0) {
        st->pos[index] = st->info->xamplitude * (cos((double)the_time / 100.0 * st->info->xspeed) * (st->info->half_width / 2)) + st->info->half_width;
    }
    else {
        st->pos[index] = st->info->yamplitude * (sin((double)the_time / 100.0 * st->info->yspeed) * (st->info->half_height / 2)) + st->info->half_height;
    }
}
