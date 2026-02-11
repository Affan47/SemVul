gamgi_expat_export_atom (gamgi_window *window, FILE *fp,
int depth_parent, int *depth_last, gamgi_bool *error, int element,
double mass, double radius, float red, float green, float blue)
{
gamgi_bool output = FALSE;

gamgi_expat_export_config_atom_local (window, fp, depth_parent,
depth_last, &output, error, element, mass, radius, red, green, blue);

if (output == TRUE) static_end (fp, "/>", error);
}
