_pack_pending_job_details(struct job_details *detail_ptr,
				      Buf buffer, uint16_t protocol_version)
{
	if (protocol_version >= SLURM_2_3_PROTOCOL_VERSION) {
		if (detail_ptr) {
			pack16(detail_ptr->shared, buffer);
			pack16(detail_ptr->contiguous, buffer);
			pack16(detail_ptr->cpus_per_task, buffer);
			pack16(detail_ptr->pn_min_cpus, buffer);

			pack32(detail_ptr->pn_min_memory, buffer);
			pack32(detail_ptr->pn_min_tmp_disk, buffer);

			packstr(detail_ptr->req_nodes, buffer);
			pack_bit_fmt(detail_ptr->req_node_bitmap, buffer);

			packstr(detail_ptr->exc_nodes, buffer);
			pack_bit_fmt(detail_ptr->exc_node_bitmap, buffer);

			pack_multi_core_data(detail_ptr->mc_ptr, buffer,
					     protocol_version);
		} else {
			pack16((uint16_t) 0, buffer);
			pack16((uint16_t) 0, buffer);
			pack16((uint16_t) 0, buffer);
			pack16((uint16_t) 0, buffer);

			pack32((uint32_t) 0, buffer);
			pack32((uint32_t) 0, buffer);

			packnull(buffer);
			packnull(buffer);
			packnull(buffer);
			packnull(buffer);

			pack_multi_core_data(NULL, buffer, protocol_version);
		}
	} else {
		error("_pack_pending_job_details: protocol_version "
		      "%hu not supported", protocol_version);
	}
}
