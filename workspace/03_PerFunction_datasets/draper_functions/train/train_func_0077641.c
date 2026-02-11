discoFinished()
{
	JT_DiscoInfo *disco = (JT_DiscoInfo*)sender();
	Q_ASSERT(disco);
	if (disco->success()) {
		emit getDiscoInfo_success(disco->jid(), disco->node(), disco->item());
	}
	else {
		emit getDiscoInfo_error(disco->jid(), disco->node(), disco->statusCode(), disco->statusString());
	}
}
