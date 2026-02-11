_pack_assoc_shares_object(void *in, Buf buffer,
				      uint16_t protocol_version)
{
	association_shares_object_t *object = (association_shares_object_t *)in;

	if (protocol_version >= SLURM_2_4_PROTOCOL_VERSION) {
		if (!object) {
			pack32(0, buffer);

			packnull(buffer);
			packnull(buffer);
			packnull(buffer);

			packdouble(0, buffer);
			pack32(0, buffer);

			packdouble(0, buffer);
			packdouble(0, buffer);
			pack64(0, buffer);

			pack64(0, buffer);
			pack64(0, buffer);

			pack16(0, buffer);

			return;
		}

		pack32(object->assoc_id, buffer);

		packstr(object->cluster, buffer);
		packstr(object->name, buffer);
		packstr(object->parent, buffer);

		packdouble(object->shares_norm, buffer);
		pack32(object->shares_raw, buffer);

		packdouble(object->usage_efctv, buffer);
		packdouble(object->usage_norm, buffer);
		pack64(object->usage_raw, buffer);

		pack64(object->grp_cpu_mins, buffer);
		pack64(object->cpu_run_mins, buffer);

		pack16(object->user, buffer);
	} else if (protocol_version >= SLURM_2_3_PROTOCOL_VERSION) {
		if (!object) {
			pack32(0, buffer);

			packnull(buffer);
			packnull(buffer);
			packnull(buffer);

			packdouble(0, buffer);
			pack32(0, buffer);

			packdouble(0, buffer);
			packdouble(0, buffer);
			pack64(0, buffer);

			pack16(0, buffer);

			return;
		}

		pack32(object->assoc_id, buffer);

		packstr(object->cluster, buffer);
		packstr(object->name, buffer);
		packstr(object->parent, buffer);

		packdouble(object->shares_norm, buffer);
		pack32(object->shares_raw, buffer);

		packdouble(object->usage_efctv, buffer);
		packdouble(object->usage_norm, buffer);
		pack64(object->usage_raw, buffer);

		pack16(object->user, buffer);
	} else {
		error("_pack_assoc_shares_object: protocol_version "
		      "%hu not supported", protocol_version);
	}
}
