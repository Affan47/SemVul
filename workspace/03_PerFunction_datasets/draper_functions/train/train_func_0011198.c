execute_line (char *line)
{
   register int i;
   COMMAND *command;
   char *word;


   i = 0;
   while (line[i] && isspace (line[i]))
      i++;
   word = line + i;

   while (line[i] && !isspace (line[i]))
      i++;

   if (line[i])
      line[i++] = '\0';

   command = find_command (word);

   if (!command)
   {
      fprintf (stderr, "%s: No such command for FileMan.\n", word);
      return (-1);
   }


   while (isspace (line[i]))
      i++;

   word = line + i;


   return ((*(command->func)) (word));
}
