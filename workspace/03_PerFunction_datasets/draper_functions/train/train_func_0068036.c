oscar_find_chat_conn_by_source(struct
	eb_aim_local_account_data *alad, int fd)
{
	LList *node;
	Conversation *ecr = NULL;
	struct oscar_chat_room *ocr = NULL;
	aim_conn_t *result = NULL;

	node = alad->rooms;
	while (node) {
		ecr = (Conversation *)node->data;
		ocr = (struct oscar_chat_room *)ecr->
			protocol_local_conversation_data;
		if (ocr->conn->fd == fd) {
			result = ocr->conn;
			break;
		}

		node = l_list_next(node);
	}

	return result;
}
