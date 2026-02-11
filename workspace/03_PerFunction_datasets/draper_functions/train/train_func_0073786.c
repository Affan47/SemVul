page_switch( GtkWidget *widget, GtkNotebookPage *page, gint page_num )
{
	if( usuario.play>=PLAY ) {
		usuario.usrfrom = usuario.pages[ page_num ];
		bnwrite(usuario.sock,BN_READ"=%i",usuario.usrfrom);
	}
	return TRUE;
}
