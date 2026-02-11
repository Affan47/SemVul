p_delta_color(t_color *val, t_color *val_from, t_color *val_to, gint32 total_steps, gdouble current_step)
{
    double     delta;
    guint l_idx;

    if(total_steps < 1) return;

    for(l_idx = 0; l_idx < 3; l_idx++)
    {
       delta = ((double)(val_to->color[l_idx] - val_from->color[l_idx]) / (double)total_steps) * ((double)total_steps - current_step);
       val->color[l_idx]  = val_from->color[l_idx] + delta;

       if(gap_debug) printf("DEBUG: p_delta_color[%d] total: %d  from: %d to: %d curr: %d    delta: %f  current_step: %f\n",
                                  (int)l_idx, (int)total_steps,
                                  (int)val_from->color[l_idx], (int)val_to->color[l_idx], (int)val->color[l_idx],
                                  delta, current_step);
    }
}
