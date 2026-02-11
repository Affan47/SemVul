ex_loop( gpointer data, gint que_sock, GdkInputCondition GDK_INPUT_READ)
{
	int i,j,k,client_len;
        char str[150];
        struct sockaddr client;

	client_len = sizeof(client);
	k = que_sock;

	if( que_sock==usuario.sock ) {
		if( (que_sock=accept(usuario.sock, (struct sockaddr *) &client,&client_len)) < 0 ) {
			perror("accept error");
			return;
		}
	}

	if( (j=accept_new_player(que_sock)) < 0)
		return;

	i = gdk_input_add( que_sock, GDK_INPUT_READ, play_batnav, NULL );
	if(i<0) {
		usuario.nro_fd[j]=-1;
		usuario.nro_tot[j]=DISCON;
		close(que_sock);
		return;
	}

	usuario.tag[j]=i;

        find_inaddr(que_sock,str,sizeof(str)-1);

	say_in_clist( j, C_HOSTNAME, str);
	say_in_clist( j, C_STATUS, _(st_nombres[CONNEC].nombre) );
	return;
}
