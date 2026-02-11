help_cmd(UAContext *ua, const char *cmd)
{
   int i;
   ua->send_msg(_("  Command       Description\n  =======       ===========\n"));
   for (i=0; i<comsize; i++) {
      if (ua->argc == 2) {
         if (!strcasecmp(ua->argk[1], commands[i].key)) {
            ua->send_msg(_("  %-13s %s\n\nArguments:\n\t%s\n"), commands[i].key,
                         commands[i].help, commands[i].usage);
            break;
         }
      } else {
         ua->send_msg(_("  %-13s %s\n"), commands[i].key, commands[i].help);
      }
   }
   if (i == comsize && ua->argc == 2) {
      ua->send_msg(_("\nCan't find %s command.\n\n"), ua->argk[1]);
   }
   ua->send_msg(_("\nWhen at a prompt, entering a period cancels the command.\n\n"));
   return 1;
}
