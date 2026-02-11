sock_bind(struct in_addr bind_add, unsigned short port,
		int maxlinelen,void (*print)(char *))
{
struct sock_state_t *tmp;
char infostring[]="Ip address xxx.xxx.xxx.xxx real port xxxxx";

tmp = (struct sock_state_t *) malloc(sizeof(struct sock_state_t));
if(tmp == NULL)
	return NULL;

tmp->maxlinelen = maxlinelen;
tmp->hostname  = strdup("localhost");
tmp->ipaddress = strdup("255.255.255.255");
tmp->prb = recvBufferCreate(maxlinelen);
tmp->print = print;
tmp->error_occurred = 0;


tmp->socket = sockopen( NULL , bind_add , port);

if ( tmp->socket == -1 )
	{
	sock_error("sockopen",-1,tmp);
	fprintf(stderr,"Unable to bind on %s:%u\n",inet_ntoa(bind_add),port);
	free(tmp);
	exit(1);
	}


get_info(tmp);
sprintf(infostring,"Ip address %s real port %ld",tmp->ipaddress,tmp->realport);
sock_info(infostring,tmp);


if (listen(tmp->socket, 5) == -1) {
		sockerror("socklisten(listen)");
		exit(0);
	}

return (tmp);
}
