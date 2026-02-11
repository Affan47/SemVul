onConnect(Connection *conn)
{
	LOG("backend connected, conn=%p, fd=%d", conn, conn->getSocket().getFd());

	RequestContext *ctx = static_cast<RequestContext*>(conn->getData());
	if(ctx->timer){
		pLoop->stopTimer(ctx->timer);
		ctx->timer = 0;
	}

	if(ctx->abort){
		EV_INVOKE(cbHandler, ctx);
		CTX_RELEASE(ctx);
	}else{
		request(ctx);
	}
}
