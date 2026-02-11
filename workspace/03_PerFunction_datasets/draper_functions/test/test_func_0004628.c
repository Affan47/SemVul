maildb_txt_store_mail(int char_id, struct mail_data *md)
{
	char filename[1056];
	FILE *fp;
	unsigned int i;

	nullpo_retr(false, md);

	sprintf(filename, "%s%d.txt", mail_dir, char_id);

	fp = fopen(filename, "a");
	if(fp == NULL)
	{
		printf("maildb_txt_store_mail: can't write [%s] !!! data is lost !!!\n", filename);
		return false;
	}

	fprintf(fp, "%u,%d\t%s\t%s\t%s\t%d\t%u,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u\t%u\t%u\t",
		md->mail_num, md->read, md->char_name, md->receive_name, md->title, md->zeny,
		md->item.id, md->item.nameid, md->item.amount, md->item.equip,
		md->item.identify, md->item.refine, md->item.attribute,
		md->item.card[0], md->item.card[1], md->item.card[2], md->item.card[3], md->item.limit,
		md->times, md->body_size);

	for(i = 0; i < md->body_size; i++) {
		fprintf(fp, "%02X", (unsigned char)(md->body[i]));
	}
	fprintf(fp, NEWLINE);
	fclose(fp);

	return true;
}
