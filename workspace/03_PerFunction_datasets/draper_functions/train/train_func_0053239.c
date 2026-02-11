HTTP_SendAndReceive(SOCKET http_socket, const char* request, const char* server_name)
{
	char recvbuffer[HTTP_REQUEST_BUFFER];


	if (send(http_socket, request, strlen(request) + 1, 0) < 0) {
		printf("Couldn't send to HTTP server\n");
		closesocket(http_socket);
		return;
	}


	int l = recv(http_socket, recvbuffer, HTTP_REQUEST_BUFFER, 0);
	if (l > 0) {
		recvbuffer[l] = '\0';
	}
	else {
		recvbuffer[0] = '\0';
	}
	if (!strstarts(recvbuffer, "HTTP/1.1 200 OK")) {
		printf("HTTP server '%s' replied with an error:\n", server_name);
		printf("%s\n---\n", recvbuffer);
	}

	closesocket(http_socket);
}
