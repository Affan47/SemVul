nondestructive_readstr(out, in, limit)
char out[];
char **in;
int limit;

{
  int i;
  i = 0;
  while ((isalpha(*(*in+i))) && (i < limit-1)) {
    out[i] = *(*in+i);
    i = i + 1;
  };
  out[i] = '\0';
}
