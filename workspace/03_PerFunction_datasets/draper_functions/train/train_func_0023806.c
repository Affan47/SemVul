_ecore_getopt_help_print_replace_program(FILE               *fp,
                                         const Ecore_Getopt *parser __UNUSED__,
                                         const char         *text)
{
   do
     {
        const char *d = strchr(text, '%');

        if (!d)
          {
             fputs(text, fp);
             break;
          }

        if (fwrite(text, 1, d - text, fp) != (size_t)(d - text))
          return;
        d++;
        if (strncmp(d, "prog", sizeof("prog") - 1) == 0)
          {
             fputs(prog ? prog : "???", fp);
             d += sizeof("prog") - 1;
          }
        else
          {
             if (d[0] == '%')
               d++;
             fputc('%', fp);
          }

        text = d;
     }
   while (text[0] != '\0');

   fputc('\n', fp);
}
