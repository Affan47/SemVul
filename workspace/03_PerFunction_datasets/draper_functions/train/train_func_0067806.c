add_socket(socket_queue **sock, int new_socket)
{
	int Cnt = 0;


	if ((*sock) == NULL)
	{
		if (!((*sock) = (socket_queue*) calloc(2,sizeof(socket_queue))))
			return NO_MEMORY;

 		(*sock)[0].descriptor = new_socket;
 		(*sock)[1].descriptor = NO_SOCKET;
 	}
 	else
 	{
		Cnt = socket_size((*sock));
 		(*sock) = (socket_queue*) realloc((*sock),sizeof(socket_queue)*(Cnt+2));
 		memset(&((*sock)[Cnt+1]),0,sizeof(socket_queue));
 		(*sock)[Cnt+1].descriptor = NO_SOCKET;

 		(*sock)[Cnt].descriptor = new_socket;
 	}

	if (init_socket(&((*sock)[Cnt])))
 		return NO_MEMORY;

	return 0;
}
