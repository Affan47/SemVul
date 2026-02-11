trim(const string& input)
{
   string app;
   int strend = input.size() - 1;
   int strsta = 0;

   while (input[strsta] == ' ' && strsta < strend) strsta++;
   while (input[strend] == ' ' && strend >= 0) strend--;

   if (strend >= strsta) return app = input.substr(strsta, strend - strsta + 1);

   return "";
}
