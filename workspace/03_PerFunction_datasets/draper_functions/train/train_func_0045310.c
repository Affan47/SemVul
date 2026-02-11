atcommand_misceffect(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	int effno = 0, id = 0;
	struct block_list *bl = NULL;

	nullpo_retr(-1, sd);

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %d", &effno, &id) < 1)
		return -1;

	if (id > 0)
		bl = map_id2bl(id);
	if (bl == NULL || bl->prev == NULL)
		bl = &sd->bl;

	clif_misceffect2(bl,effno);

	return 0;
}
