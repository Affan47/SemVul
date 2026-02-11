get_static_function(char *function, char *method_name, char *method_sig)
{
char *s;
int ptr = 0;

  s = method_name;
  while (*s != 0)
  {
    function[ptr++] = *s;
    s++;
  }

  function[ptr++] = '_';
  s = method_sig + 1;
  while(*s != 0)
  {
    if (*s == ')') { break; }
    if (*s == '[') { function[ptr++] = 'a'; }
    else { function[ptr++] = *s; }

    s++;
  }

  if (ptr > 1 && function[ptr-1] == '_') { function[ptr-1] = 0; }
  function[ptr] = 0;
}
