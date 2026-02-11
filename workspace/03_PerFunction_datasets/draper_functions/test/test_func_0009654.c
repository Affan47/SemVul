execute_command(char *name, struct pnode *parms)
{
  int value = 0;
  int i = 0;
  gp_boolean found_command = false;

  while (i < NUM_COMMAND) {
    if (strcasecmp(name, commands[i].name) == 0) {
      found_command = true;
      break;
    }
    i++;
  }

  if (!found_command) {
    script_error("invalid script command", name);
  } else {
    value = (*(lkrfunc*)commands[i].address)(name, parms);
  }

  return value;
}
