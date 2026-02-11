on_oni__button_cancel_clicked          (GtkButton       *button,
                                        GapOnionMainGlobalParams *gpp)
{
 if(gap_debug) printf("CB: on_oni__button_cancel_clicked\n");

 if(gpp)
 {
   gpp->run = GAP_ONION_RUN_CANCEL;
   gtk_widget_destroy (gpp->main_dialog);
 }
 gtk_main_quit ();
}
