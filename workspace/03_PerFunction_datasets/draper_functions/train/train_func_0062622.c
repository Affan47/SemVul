cb_gen_password(GtkWidget *widget, gpointer data)
{
   GtkWidget *entry;
   int   i,
   length,
   alpha_size,
   numer_size;
   char alpha[] = "abcdfghjklmnpqrstvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
   char numer[] = "1234567890";
   char passwd[MAX_KR_PASS + 1];

   jp_logf(JP_LOG_DEBUG, "KeyRing: cb_gen_password\n");

   entry=data;

   srand(time(NULL) * getpid());
   alpha_size = strlen(alpha);
   numer_size = strlen(numer);

   length = rand() % (MAX_KR_PASS - MIN_KR_PASS) + MIN_KR_PASS;

   for (i = 0; i < length; i++) {
      if ((i % 2) == 0) {
         passwd[i] = alpha[rand() % alpha_size];
      } else {
         passwd[i] = numer[rand() % numer_size];
      }
   }

   passwd[length] = '\0';

   gtk_entry_set_text(GTK_ENTRY(entry), passwd);

   return;
}
