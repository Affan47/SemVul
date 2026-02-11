slurm_free_block_info_members(block_info_t *block_info)
{
	if(block_info) {
		xfree(block_info->bg_block_id);
		xfree(block_info->blrtsimage);
		xfree(block_info->ionode_inx);
		xfree(block_info->ionode_str);
		xfree(block_info->linuximage);
		xfree(block_info->mloaderimage);
		xfree(block_info->mp_inx);
		xfree(block_info->mp_str);
		xfree(block_info->ramdiskimage);
		xfree(block_info->reason);
	}
}
