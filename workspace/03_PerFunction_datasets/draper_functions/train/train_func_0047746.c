my_rl_list_possib(char *token, char ***av)
{
   int i, num, total = 0;
   char **copy;

   for (num = 0; list[num]; num++)
      ;
   copy = (char **) malloc (num * sizeof(char *));
   for (i = 0; i < num; i++)
   {
      if (!strncmp (list[i], token, strlen (token)))
      {
         copy[total] = strdup (list[i]);
         total ++;
      }
   }
   *av = copy;

   return total;
}
