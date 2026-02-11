lst_line(char *line)
{
  if (state.lst.f) {
    if (state.lst.linesperpage != 0) {
      if ((state.lst.lineofpage++ % state.lst.linesperpage) == 0) {
        lst_throw();
        lst_line("LOC  OBJECT CODE     LINE SOURCE TEXT");
        lst_line("  VALUE");
        lst_line(" ");
      }
    }
    fprintf(state.lst.f, "%s\n", line);
    state.lst.line_number++;
    cod_lst_line(COD_NORMAL_LST_LINE);
  }
}
