define(def, file)
   char   *def;
   struct inclist   *file;
{
    char *val;


    val = def;
    while (isalnum(*val) || *val == '_')
   val++;
    if (*val)
   *val++ = '\0';
    while (*val == ' ' || *val == '\t')
   val++;

    if (!*val)
   val = "1";
    define2(def, val, file);
}
