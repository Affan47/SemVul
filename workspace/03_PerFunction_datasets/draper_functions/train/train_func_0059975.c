ccd_reduce_release(struct ccd_reduce *ccdr)
{
	if (ccdr == NULL)
		return;
	g_return_if_fail(ccdr->ref_count >= 1);
	if (ccdr->ref_count > 1) {
		ccdr->ref_count--;
		return;
	}
	image_file_release(ccdr->bias);
	image_file_release(ccdr->dark);
	image_file_release(ccdr->flat);
	if (ccdr->wcs)
		wcs_release(ccdr->wcs);
	if (ccdr->recipe)
		free(ccdr->recipe);

	free(ccdr);
}
