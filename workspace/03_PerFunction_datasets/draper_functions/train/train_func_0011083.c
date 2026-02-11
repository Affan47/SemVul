luaConnSessionId(lua_State *pState)
{
	Connection *pConn = (Connection*)lua_touserdata(pState, -1);
	if(!pConn){
		return luaL_error(pState, "invalid connection");
	}

	lua_pop(pState, 1);

	ClientData *pData = (ClientData*)pConn->getData();
	if(pData){
		lua_pushlstring(pState, pData->session.getId(), SID_LENGTH);
	}

	return 1;
}
