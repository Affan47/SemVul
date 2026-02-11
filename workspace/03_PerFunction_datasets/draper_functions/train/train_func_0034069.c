get_duration(char *str)
{
  char *multchar;
  int mult;
  char save;
  int duration;

  for(multchar=str; *multchar != '\0'; multchar++);
  if(multchar != str) { multchar--; }
  if(*multchar == '\0' || isdigit(*multchar)) { mult = 1; multchar++; }
  else if(*multchar == 'M') { mult = 60; }
  else if(*multchar == 'H') { mult = 60*60; }
  else if(*multchar == 'd') { mult = 60*60*24; }
  else if(*multchar == 'w') { mult = 60*60*24*7; }
  else if(*multchar == 'f') { mult = 60*60*24*7*2; }
  else if(*multchar == 'm') { mult = 60*60*24*30; }
  else if(*multchar == 'y') { mult = 60*60*24*365; }
  else
  {
    fprintf(stderr, "invalid multiplier: %c\n", *multchar);
    fprintf(stderr, "valid multipliers:\n");
    fprintf(stderr, "  %c -> %s (%d)\n", 'M', "Minute",    60);
    fprintf(stderr, "  %c -> %s (%d)\n", 'H', "Hour",      60*60);
    fprintf(stderr, "  %c -> %s (%d)\n", 'd', "day",       60*60*24);
    fprintf(stderr, "  %c -> %s (%d)\n", 'w', "week",      60*60*24*7);
    fprintf(stderr, "  %c -> %s (%d)\n", 'f', "fortnight", 60*60*24*7*2);
    fprintf(stderr, "  %c -> %s (%d)\n", 'm', "month",     60*60*24*30);
    fprintf(stderr, "  %c -> %s (%d)\n", 'y', "year",      60*60*24*365);
    exit(1);
  }
  save = *multchar;
  *multchar = '\0';
  duration = strtol(str, NULL, 0) * mult;
  *multchar = save;

  return(duration);
}
