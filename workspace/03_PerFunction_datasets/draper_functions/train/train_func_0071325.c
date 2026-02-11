static_object_light (gamgi_light *light,
gamgi_window *window, gamgi_object *scope, FILE *fp, int depth_parent,
int *depth_last, int *id, gamgi_bool *error)
{
int column, depth;

depth = depth_parent + 1;
if (depth > *depth_last)
  gamgi_io_file_fprintf (fp, ">", error);
column = strlen ("<light") + static_start (fp, "<light", depth, error);
*depth_last = depth;

gamgi_expat_export_object_light (light, fp, depth, &column, id, error);

if (depth < *depth_last)
  static_start (fp, "</light>", depth, error);
else
  static_end (fp, "/>", error);
}
