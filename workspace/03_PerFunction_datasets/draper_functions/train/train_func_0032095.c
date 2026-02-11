addCancelItem(connection_t *cxn,
			      char *folder, int folderlen,
			      char *msgid, int msgidlen,
			      Article art, int must)
{
    control_item_t *item;
    conn_ret result;
    int i;

    ASSERT(folder); ASSERT(msgid); ASSERT(cxn);


    for (i = 0; i < folderlen; i++) ASSERT(!isspace((unsigned char) folder[i]));
    for (i = 0; i < msgidlen; i++) ASSERT(!isspace((unsigned char) msgid[i]));


    item = xcalloc (1, sizeof(control_item_t));

    item->folder = xcalloc(folderlen+1, 1);
    memcpy(item->folder, folder, folderlen);
    item->folder[folderlen] = '\0';

    item->msgid = xcalloc (msgidlen+1, 1);
    memcpy(item->msgid, msgid, msgidlen);
    item->msgid[msgidlen] = '\0';

    item->article = art;


    result = AddToQueue(&(cxn->imap_controlMsg_q), item, CANCEL_MSG, (art != NULL), must);
    if (result != RET_OK) {
	d_printf(1,"%s:%d addCancelItem(): "
		 "I thought we had in space in [imap] queue "
		 "but apparently not\n",
		 hostPeerName (cxn->myHost), cxn->ident);


	free(item->folder);
	free(item->msgid);
	free(item);

	return result;
    }

    return RET_OK;
}
