html_output_string(FILTER_S *f, char *s)
{
    for(; *s; s++)
      html_output(f, *s);
}
