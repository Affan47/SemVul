button_fcioption(GtkWidget *w)
{
	GtkWidget* Table;
	GtkWidget* button;
	guint i;
	guint j;
        guint ColonneT=2;
        guint LigneT=3;
	char *LabelButton[2][3]={
        {_("Defining the orbitals"),
         _("Defining the closed-shell orbitals"),
         _("Defining the state symmetry"),
        },
        {_("Defining the occupied orbitals"),
         _("Defining the Frozen-core orbitals"),
         "00"
         }
	};

  Table = gtk_table_new(LigneT,ColonneT,TRUE);
  gtk_container_add(GTK_CONTAINER(w),Table);

  for ( i = 0;i<LigneT;i++)
	  for ( j = 0;j<ColonneT;j++)
  {
    if(strcmp(LabelButton[j][i],"00"))
          {
	  button = gtk_button_new_with_label(LabelButton[j][i]);

          g_signal_connect(G_OBJECT(button), "clicked",
                            (GCallback)Traite_ci_Option,(gpointer )LabelButton[j][i]);

	  gtk_table_attach(GTK_TABLE(Table),button,j,j+1,i,i+1,
		  (GtkAttachOptions)(GTK_FILL | GTK_EXPAND) ,
		  (GtkAttachOptions)(GTK_FILL | GTK_EXPAND),
		  1,1);
          gtk_widget_show (button);
         }

  }
  gtk_widget_show (Table);

}
