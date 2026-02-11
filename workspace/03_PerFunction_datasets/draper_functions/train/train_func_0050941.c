p_delta_gint(gint *val, gint val_from, gint val_to, gint32 total_steps, gdouble current_step)
{
    double     delta;

    if(total_steps < 1) return;

    delta = ((double)(val_to - val_from) / (double)total_steps) * ((double)total_steps - current_step);
    *val  = ROUND(val_from + delta);
}
