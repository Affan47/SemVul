on_mw__checkbutton_multilayer_toggled  (GtkToggleButton *togglebutton,
                                        GapVexMainGlobalParams *gpp)
{
 GtkWidget *wgt;

 if(gap_debug) printf("CB: on_mw__checkbutton_multilayer_toggled\n");
 if(gpp == NULL) return;

 wgt = gpp->mw__checkbutton_multilayer;

 if (GTK_TOGGLE_BUTTON (wgt)->active)
 {
    gpp->val.multilayer = TRUE;
 }
 else
 {
    gpp->val.multilayer = FALSE;
 }
 p_update_wgt_sensitivity(gpp);
}
