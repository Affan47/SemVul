log_inode_reference(struct duptree *dt, osi_list_t *tmp, int inval)
{
	char reftypestring[32];
	struct inode_with_dups *id;

	id = osi_list_entry(tmp, struct inode_with_dups, list);
	if (id->dup_count == 1)
		sprintf(reftypestring, "as %s", reftypes[get_ref_type(id)]);
	else
		sprintf(reftypestring, "%d/%d/%d/%d",
			id->reftypecount[ref_is_inode],
			id->reftypecount[ref_as_data],
			id->reftypecount[ref_as_meta],
			id->reftypecount[ref_as_ea]);
	if (inval)
		log_warn( _("Invalid "));
	log_warn( _("Inode %s (%lld/0x%llx) has %d reference(s) to "
		    "block %llu (0x%llx) (%s)\n"), id->name,
		  (unsigned long long)id->block_no,
		  (unsigned long long)id->block_no, id->dup_count,
		  (unsigned long long)dt->block,
		  (unsigned long long)dt->block, reftypestring);
}
