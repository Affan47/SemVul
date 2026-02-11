crosscor_sanitize_args(CrosscorArgs *args)
{
    args->result = MIN(args->result, GWY_CROSSCOR_LAST-1);
    args->search_x = CLAMP(args->search_x, 0, 100);
    args->search_y = CLAMP(args->search_y, 0, 100);
    args->window_x = CLAMP(args->window_x, 0, 100);
    args->window_y = CLAMP(args->window_y, 0, 100);
    args->threshold = CLAMP(args->threshold, -1.0, 1.0);
    args->add_ls_mask = !!args->add_ls_mask;
}
