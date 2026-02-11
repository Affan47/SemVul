static_config_light (gamgi_window *window,
FILE *fp, int depth_parent, int *depth_last, gamgi_bool *error)
{
gamgi_bool output = FALSE;

gamgi_expat_export_config_light (window, fp,
depth_parent, depth_last, &output, error);

if (output == TRUE) static_end (fp, "/>", error);
}
