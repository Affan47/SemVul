ShowXMLOfFlags(const char *prog_name) {
  vector<CommandLineFlagInfo> flags;
  GetAllFlags(&flags);


  fprintf(stdout, "<?xml version=\"1.0\"?>\n");

  fprintf(stdout, "<AllFlags>\n");

  fprintf(stdout, "<program>%s</program>\n",
          XMLText(Basename(prog_name)).c_str());
  fprintf(stdout, "<usage>%s</usage>\n",
          XMLText(ProgramUsage()).c_str());

  for (vector<CommandLineFlagInfo>::const_iterator flag = flags.begin();
       flag != flags.end();
       ++flag) {
    if (flag->description != kStrippedFlagHelp)
      fprintf(stdout, "%s\n", DescribeOneFlagInXML(*flag).c_str());
  }

  fprintf(stdout, "</AllFlags>\n");
}
