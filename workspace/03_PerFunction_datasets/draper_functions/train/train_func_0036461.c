gf_isom_fdm_del(GF_FileDataMap *ptr)
{
	if (!ptr || (ptr->type != GF_ISOM_DATA_FILE)) return;
	if (ptr->bs) gf_bs_del(ptr->bs);
	if (ptr->stream && !ptr->is_stdout) fclose(ptr->stream);

#ifndef GPAC_DISABLE_ISOM_WRITE
	if (ptr->temp_file) {
		gf_delete_file(ptr->temp_file);
		gf_free(ptr->temp_file);
	}
#endif
	gf_free(ptr);
}
