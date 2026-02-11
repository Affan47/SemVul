PingAllPlayer(){
	int i;
	for (i = 1; i <= sv_maxplayers; i++)
		if (player[i].used == 1 && player[i].joinstatus >= 4)
			player[i].start = mtime();

	byte buffer[] = {249,0,32,191,0};
	SendToAll(buffer, 5, 0);
}
