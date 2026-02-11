ordin(int n)
{
static char buffer[8];
char *p = buffer;
sprintf(p, "%d", n);
while (*p != 0) p++;
switch (n%10)
  {
  case 1: strcpy(p, "st"); break;
  case 2: strcpy(p, "nd"); break;
  case 3: strcpy(p, "rd"); break;
  default: strcpy(p, "th"); break;
  }
return buffer;
}
