token_lost( char *str )
{
	int j,x;

	x=atoi(str);

	if(x<0 || x>=MAXPLAYER)
		return;

	if(x==usuario.numjug) {
		usuario.play=PERDIO;

		textfill(0,_("You LOST the game!"));
		g_box_lost();
		return;
	}
	usuario.names[x][0]=0;
	textfill(0,_("Player %i lost the game"),x);


	if(x==usuario.usrfrom) {
		poner_proximo_jugador();

		if(usuario.usrfrom==usuario.numjug)
			poner_proximo_jugador();
		bnwrite(usuario.sock,BN_READ"=%i",usuario.usrfrom);
	}

	j=sacar_usrpage(x);
	if(j==-1) {
		textfill(1,"token_lost: sacar_usrpage(%i) error",x);
		return;
	}
	remove_page( j );
	return;
}
