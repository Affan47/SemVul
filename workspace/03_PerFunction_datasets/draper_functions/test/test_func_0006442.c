scan_statistics(gboolean reload)
{
    FILE *netstat;
    gchar buffer[256];
    gchar *netstat_path;

    SCAN_START();

    g_free(__statistics);
    __statistics = g_strdup("");

    if ((netstat_path = find_program("netstat"))) {
      gchar *command_line = g_strdup_printf("%s -s", netstat_path);

      if ((netstat = popen(command_line, "r"))) {
        while (fgets(buffer, 256, netstat)) {
          if (!isspace(buffer[0]) && strchr(buffer, ':')) {
            gchar *tmp;

            tmp = g_ascii_strup(strend(buffer, ':'), -1);

            __statistics = h_strdup_cprintf("[%s]\n",
                                            __statistics,
                                            tmp);

            g_free(tmp);
          } else if (isdigit(buffer[4])) {
            gchar *tmp1 = buffer + 4,
                  *tmp2 = tmp1;

            while (*tmp2 && !isspace(*tmp2)) tmp2++;
            *tmp2 = 0;
            tmp2++;

            *tmp2 = toupper(*tmp2);

            __statistics = h_strdup_cprintf("%s=%s\n",
                                            __statistics,
                                            g_strstrip(tmp1),
                                            g_strstrip(tmp2));
          }
        }

        pclose(netstat);
      }

      g_free(command_line);
      g_free(netstat_path);
    }

    SCAN_END();
}
