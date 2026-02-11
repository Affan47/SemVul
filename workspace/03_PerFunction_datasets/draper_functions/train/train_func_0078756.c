decrease_freqstep(GtkWidget *widget __attribute__((unused)),
		       gpointer user_data __attribute__((unused))){
  if(fsidx>0) fsidx--; freqstep=freqsteptab[fsidx];
  showtextstat();
}
