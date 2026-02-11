mjpg_cleanup(void *handle)
{
    struct mjpeg_compress *h = handle;
    int i;

    if (ng_debug > 1)
	fprintf(stderr,"mjpg_cleanup\n");

    jpeg_destroy_compress(&h->mjpg_cinfo);
    for (i = 0; i < 3; i++)
	if (NULL != h->mjpg_ptrs[i])
	    free(h->mjpg_ptrs[i]);
    free(h);
}
