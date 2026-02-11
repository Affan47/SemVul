getcov_nugget(G_GNUC_UNUSED gdouble aspect)
{
    return 1.0 - (1.0 - G_PI/4.0)/MAX(aspect, 1.0/aspect);
}
