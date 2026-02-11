smb2_seq_num_into_buf(struct TCP_Server_Info *server,
		      struct smb2_sync_hdr *shdr)
{
	unsigned int i, num = le16_to_cpu(shdr->CreditCharge);

	shdr->MessageId = get_next_mid64(server);

	for (i = 1; i < num; i++)
		get_next_mid(server);
}
