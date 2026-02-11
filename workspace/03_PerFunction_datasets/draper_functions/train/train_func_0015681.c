GetHexInput (char *cmdLine, char *prompt, char *cDefault, int c_size)
{
   char buffer[256];
   char buffer2[8];
   char two[3];
   char *ptr;
   int count;
   char *sptr;
   char *result;

   memset (buffer, 0, sizeof (buffer));
   memset (buffer2, 0, sizeof (buffer2));
   memset (cmdLine, 0, c_size);
   printf ("%s [%s] >", prompt,
           cDefault != NULL ? HexToAscii (cDefault, 8, buffer2) : "(none)");
   result = fgets (buffer, sizeof(buffer), stdin);
   sptr = strtok(buffer, TOKENS);
   ptr = sptr;
   count = 0;
   if (ptr)
   {
	   while (*ptr)
		   {
		   memset (two, 0, sizeof (two));
		   memcpy (two, ptr, 2);
		   sscanf (two, "%x", (int *)&cmdLine[count]);
		   count++;
		   ptr = (char *) ptr + 2;
	   }
   }

   return count;
}
