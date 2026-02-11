transport_generic_map_mem_to_cmd(struct se_cmd *cmd, struct scatterlist *sgl,
		u32 sgl_count, struct scatterlist *sgl_bidi, u32 sgl_bidi_count)
{
	if (!sgl || !sgl_count)
		return 0;


	if (cmd->se_cmd_flags & SCF_OVERFLOW_BIT) {
		pr_warn("Rejecting SCSI DATA overflow for fabric using"
			" SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC\n");
		return TCM_INVALID_CDB_FIELD;
	}

	cmd->t_data_sg = sgl;
	cmd->t_data_nents = sgl_count;
	cmd->t_bidi_data_sg = sgl_bidi;
	cmd->t_bidi_data_nents = sgl_bidi_count;

	cmd->se_cmd_flags |= SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC;
	return 0;
}
