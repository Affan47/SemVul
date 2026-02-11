sendToClient(Connection *conn, const char *data, int len)
{
	if(pScript && pScript->hasWriteProc()){
		Buffer msg(data, len);
		sendToClientByScript(conn, &msg);
	}else if(len){
		sendToClientByDefault(conn, data, len);
	}
}
