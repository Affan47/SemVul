generar( void )
{
	gint x,y,d,t,i,j;

	if( usuario.play==PLAY || usuario.play==TURN ) {

		textfill(0,_("You can't modify your board while playing."));
		return ;

	} else if( usuario.play==BOARD ) {
		textfill(0,_("You've already sent your board to the server. You can't modify it."));
		return ;

	} else {
		usuario.random = gnome_config_get_int_with_default("/gbnclient/data/random=1995",NULL);
		srandom( usuario.random );
		usuario.random = random();
		gnome_config_set_int   ("/gbnclient/data/random",  usuario.random);
		gnome_config_sync();

		for(i=0;i<10;i++) {

			for(j=0;j<10;j++)
				usuario.mitabla[i][j]=NOBARCO;
		}

		for(i=1;i<=10;i++) {
			x = 1+(int) (10.0*rand()/(RAND_MAX+1.0));
			y = 1+(int) (10.0*rand()/(RAND_MAX+1.0));
			d = (x + y) & 1;
			t = tamano( i );

			buscar_poscicion(x,y,d,t);
		}

		for(i=0;i<10;i++) {
			for(j=0;j<10;j++)
				pmicell(i,j,usuario.mitabla[i][j]);
		}
		draw_grid_left();
	}
}
