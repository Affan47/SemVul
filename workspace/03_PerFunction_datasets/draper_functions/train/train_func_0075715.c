dw_PrintFloat(FILE* f, void* element, char *format)
{
  return (fprintf(f,format ? format : "%f ",*((float*)element)) < 0) ? 0 : 1;
}
