skip_line (FILE *fp)


{
   while (nextchar != EOF && nextchar != '\n')
     nextchar = getc (fp);
   if (nextchar != EOF)
     {
       line_number ++;
       nextchar = getc (fp);
     }
}
