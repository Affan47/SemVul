Read_An_Integer(int arg_nb)
{
  char *p;
  long val = 0;

  val = strtol(read_arg[arg_nb], &p, 0);
  if (*p)
    Stream_Printf(pstm_o, "Incorrect integer\n");

  return val;
}
