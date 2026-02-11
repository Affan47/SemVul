knot_rrset_header_to_wire(const knot_rrset_t *rrset,
                                     uint8_t **pos, size_t max_size,
                                     knot_compr_t *compr, size_t *size)
{

	const size_t type_cls_ttl_len = 2 * sizeof(uint16_t) + sizeof(uint32_t);

	const size_t rrlen_len = sizeof(uint16_t);

	if (rrset->owner == NULL) {
		return KNOT_EMALF;
	}

	const uint8_t *owner;
	uint8_t owner_len;


	if (compr) {
		owner = compr->owner.wire + compr->owner.pos;
		owner_len = compr->owner.size;

	} else {
		owner = rrset->owner;
		owner_len = knot_dname_size(owner);
	}

	dbg_response("Max size: %zu, compressed owner: %s, owner size: %u\n",
	             max_size, compr ? "yes" : "no", owner_len);


	if (*size + owner_len + type_cls_ttl_len + rrlen_len > max_size) {
		dbg_rrset_detail("Header does not fit into wire.\n");
		return KNOT_ESPACE;
	}


	*pos += knot_dname_to_wire(*pos, owner, KNOT_DNAME_MAXLEN);

	dbg_rrset_detail("  Type: %u\n", rrset->type);
	knot_wire_write_u16(*pos, rrset->type);
	*pos += sizeof(uint16_t);

	dbg_rrset_detail("  Class: %u\n", rrset->rclass);
	knot_wire_write_u16(*pos, rrset->rclass);
	*pos += sizeof(uint16_t);

	dbg_rrset_detail("  TTL: %u\n", rrset->ttl);
	knot_wire_write_u32(*pos, rrset->ttl);
	*pos += sizeof(uint32_t);

	*size += owner_len + type_cls_ttl_len;

	return KNOT_EOK;
}
