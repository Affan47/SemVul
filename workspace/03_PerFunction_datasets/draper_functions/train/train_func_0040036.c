reset()
{
	if (prebuilt->blob_heap) {
		row_mysql_prebuilt_free_blob_heap(prebuilt);
	}

	reset_template(prebuilt);


	prebuilt->autoinc_last_value = 0;

	return(0);
}
