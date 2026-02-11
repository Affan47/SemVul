save_game(gchar *rules, gint score, gint *board, gint *nextcolors) {
        FILE *f;
        gchar *fname;
        time_t nowtime;
        gchar  ftime[]="0000-00-00-000000";
        gint i;

        nowtime = time(NULL);
        strftime(ftime, sizeof(ftime), "%Y-%m-%d-%H%M%S", localtime(&nowtime));
        fname = g_strconcat(getenv("HOME"), G_DIR_SEPARATOR_S, ".gtkballs",
                            G_DIR_SEPARATOR_S, ftime, ".sav", NULL);
        if((f = fopen(fname, "w")) != NULL) {
                chmod(fname, 0600);

                fprintf(f, "%s", rules);
                fprintf(f, "%010d", score);
                for(i = 0; i < rules_get_width() * rules_get_height(); i++) {
                	fprintf(f, "%02d", board[i]);
                }
                for(i = 0; i < rules_get_next(); i++) {
                	fprintf(f, "%02d", nextcolors[i]);
                }
                fclose(f);
        } else {
                return fname;
        }

        g_free(fname);

        return NULL;
}
