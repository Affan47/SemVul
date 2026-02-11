token_start_aux( char *str)
{
	int i,j,k,l;
	PARSER p;
	DELIM igualador={ '=','=','=' };
	DELIM separador={ '/',',','/' };

	p.igualador = &igualador;
	p.separador = &separador;

	strncpy(p.sig,str,sizeof(p.sig));


	j=0;k=0;l=0;
	do{
		i=parser_init( &p );

		if(p.status && j==0)
			l=atoi(p.token);

		else if(p.status && j==1)
			k=atoi(p.token);

		else if(p.status && j==2)  {
			if(k==BOARD) {
				strncpy(usuario.names[l],p.token, sizeof(usuario.names[l]));
				textfill(0,_("\t%i, %s"),l,p.token);
				label_right[l] = gtk_label_new( usuario.names[l] );
				label_right2[l] = gtk_label_new( usuario.names[l] );
				drawing_right[l] = gtk_drawing_area_new();
				gtk_drawing_area_size(GTK_DRAWING_AREA(drawing_right[l]),200,200);
				gtk_signal_connect (GTK_OBJECT (drawing_right[l]), "expose_event",
			   		(GtkSignalFunc) expose_event_right, NULL);
				gtk_signal_connect (GTK_OBJECT (drawing_right[l]), "button_press_event",
			   		(GtkSignalFunc) button_press_event_right, NULL);
				gtk_widget_set_events (drawing_right[l], GDK_EXPOSURE_MASK
			      		|GDK_BUTTON_PRESS_MASK);

				gtk_widget_show( label_right[l] );
				gtk_widget_show( label_right2[l] );
				gtk_widget_show( drawing_right[l] );
			       	gtk_notebook_append_page_menu ( GTK_NOTEBOOK(notebook_right),
					drawing_right[l],
					label_right[l],
					label_right2[l] );
			} else sacar_usrpage(l);
		}
		j++;
		j=j%3;
	} while(i);
}
