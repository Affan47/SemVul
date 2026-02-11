static_cdata_int (int size, int *array,
FILE *fp, int depth, gamgi_bool *error)
{
char string[GAMGI_ENGINE_STRING];
int column, i;


column = -1;
for (i = 0; i < size; i++)
  {
  sprintf (string, "%d", array[i]);
  gamgi_expat_export_cdata (fp, string, depth, &column, error);
  }
}
