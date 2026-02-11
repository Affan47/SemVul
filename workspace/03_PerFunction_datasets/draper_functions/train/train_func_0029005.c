GetInfoGth()
{
  guint i;
  gchar *NameOp[14]={
  		"zero", "oneint", "twoint","preface","locali",
                "eorder","energy","gradiant","step","orbital",
                "civec","coeff","printci","punchci"
  		};
  gchar *DefOp[14]={
  		"1.d-12", "1.d-12", "1.d-12","1.d-14","1.d-8",
                "1.d-4","1.d-6","1.d-2","1.d-3","1.d-5",
                "1.d-5","1.d-4","0.05","99"
  		};
  gchar *CommOp[14]={
  		_("Numerical zero"),
                _("Threshold for one-electron integrals"),
                _("Threshold for the neglect of two-electron integrals"),
                _("Threshold for test of prefactor in TWOINT"),
                _("Threshold for orbital localization"),
                _("Threshold for reordering of orbital after localization"),
                _("Convergence threshold for energy"),
                _("Convergence threshold for orbital gradient in MCSCF"),
                _("Convergence threshold for step length in MCSCF orbital optimization"),
                _("Convergence threshold for orbital optimization in the SCF program"),
                _("Convergence threshold for CI coefficients in MCSCF and reference vector in CI"),
                _("Convergence threshold for coefficients in CI and CCSD"),
                _("Threshold for printing CI coefficients"),
                _("Threshold for punching CI coefficients")
  		};
        G_CONST_RETURN gchar *chaine[14];

        chaine[0]=gtk_entry_get_text(GTK_ENTRY(gen->gth_zero));
        chaine[1]=gtk_entry_get_text(GTK_ENTRY(gen->gth_oneint));
        chaine[2]=gtk_entry_get_text(GTK_ENTRY(gen->gth_twoint));
        chaine[3]=gtk_entry_get_text(GTK_ENTRY(gen->gth_prefac));
        chaine[4]=gtk_entry_get_text(GTK_ENTRY(gen->gth_locali));
        chaine[5]=gtk_entry_get_text(GTK_ENTRY(gen->gth_eorder));
        chaine[6]=gtk_entry_get_text(GTK_ENTRY(gen->gth_energy));
        chaine[7]=gtk_entry_get_text(GTK_ENTRY(gen->gth_gradiant));
        chaine[8]=gtk_entry_get_text(GTK_ENTRY(gen->gth_step));
        chaine[9]=gtk_entry_get_text(GTK_ENTRY(gen->gth_orbital));
        chaine[10]=gtk_entry_get_text(GTK_ENTRY(gen->gth_civec));
        chaine[11]=gtk_entry_get_text(GTK_ENTRY(gen->gth_coeff));
        chaine[12]=gtk_entry_get_text(GTK_ENTRY(gen->gth_printci));
        chaine[13]=gtk_entry_get_text(GTK_ENTRY(gen->gth_punchci));

        for(i=0;i<14;i++)
        	insert_gth_option(NameOp[i],DefOp[i],chaine[i],CommOp[i]);

}
