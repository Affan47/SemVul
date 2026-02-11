_send_msg(struct block_device *block)
{
	if (!block->cntrl) {
		log_debug("Missing cntrl for dev: %s. Not sending anything.",
			  strstr(block->sysfs_path, "host"));
		return;
	}
	if (block->timestamp != timestamp) {
		if (block->ibpi != IBPI_PATTERN_FAILED_DRIVE) {
			log_info("CHANGE %s: from '%s' to '%s'.",
				 block->sysfs_path, ibpi_str[block->ibpi],
				 ibpi_str[IBPI_PATTERN_FAILED_DRIVE]);
			block->ibpi = IBPI_PATTERN_FAILED_DRIVE;
		} else {
			log_debug("DETACHED DEV '%s' in failed state",
				  strstr(block->sysfs_path, "host"));
		}
	}
	block->send_fn(block, block->ibpi);
	block->ibpi_prev = block->ibpi;
}
