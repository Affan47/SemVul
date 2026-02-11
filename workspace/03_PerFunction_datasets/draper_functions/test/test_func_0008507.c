OnJoin(int id){
	SendJoinMessage(id);
	printf("%s (#%d) has joined the game using ip %s:%d and usgn-id #%d!\n", player[id].name, id, inet_ntoa(player[id].ip), player[id].port, player[id].usgn);

	INVOKE("join", "i", id);
}
