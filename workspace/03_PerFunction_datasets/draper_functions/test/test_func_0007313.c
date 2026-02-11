ata_ering_top(struct ata_ering *ering)
{
	struct ata_ering_entry *ent = &ering->ring[ering->cursor];

	if (ent->err_mask)
		return ent;
	return NULL;
}
