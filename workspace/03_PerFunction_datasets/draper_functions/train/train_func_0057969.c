aim_tlvlist_copy(aim_tlvlist_t *orig)
{
	aim_tlvlist_t *new = NULL;

	while (orig) {
		aim_addtlvtochain_raw(&new, orig->tlv->type, orig->tlv->length,
			orig->tlv->value);
		orig = orig->next;
	}

	return new;
}
