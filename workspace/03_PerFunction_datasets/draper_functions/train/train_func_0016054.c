dlite_main(md_addr_t regs_PC,
	   md_addr_t next_PC,
	   counter_t cycle,
	   struct regs_t *regs,
	   struct mem_t *mem)
{
  char buf[512], *err_str;
  int dbreak = (break_access & (ACCESS_READ|ACCESS_WRITE)) != 0;
  static char cmd[512] = "";

  dlite_active = TRUE;
  dlite_return = FALSE;
  dlite_status(regs_PC, next_PC, cycle, dbreak, regs, mem);

  while (dlite_active && !dlite_return)
    {
      fprintf(stdout, DLITE_PROMPT);
      fflush(stdout);
      fgets(buf, 512, stdin);


      if (buf[strlen(buf)-1] == '\n')
	buf[strlen(buf)-1] = '\0';

      if (buf[0] != '\0')
	{

	  strcpy(cmd, buf);
	}


      err_str = dlite_exec(cmd, regs, mem);
      if (err_str)
	fprintf(stdout, "Dlite: error: %s\n", err_str);
    }
}
