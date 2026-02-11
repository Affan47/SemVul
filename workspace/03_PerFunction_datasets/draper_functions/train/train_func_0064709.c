free_gamelist(gchar **gamelist, gint num) {
        gint i;

        for(i = 0; i < num * 2; i++) {
        	g_free(gamelist[i]);
        }
        g_free(gamelist);
}
