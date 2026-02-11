ira_bad_reload_regno (int regno, rtx in, rtx out)
{
  return (ira_bad_reload_regno_1 (regno, in)
	  || ira_bad_reload_regno_1 (regno, out));
}
