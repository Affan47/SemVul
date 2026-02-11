msn_set_psm(MsnAccount *ma, char *message)
{
	char psm_payload[1024] = "";
	char psm_payload_size[5];
	int size = 0;

	free(ma->psm);

	size = snprintf(psm_payload, sizeof(psm_payload),
		"<Data><PSM>%s</PSM><CurrentMedia></CurrentMedia>"
		"<MachineGuid>{F26D1F07-95E2-403C-BC18-D4BFED493428}</MachineGuid>"
		"</Data>", message?message:"");

	sprintf(psm_payload_size, "%d", size);

	msn_message_send(ma->ns_connection, psm_payload[0]?psm_payload:NULL,
		MSN_COMMAND_UUX, psm_payload_size);

	ma->psm = message?strdup(message):NULL;
}
