read_gob(FILE *handle, gob_t *gob, int len)
{
	unsigned char *gob_data;
	int i;

	gob_data = malloc(len);
	fread(gob_data, 1, len, handle);

	gob->num_images = (short)((gob_data[0]) + (gob_data[1] << 8));

	gob->width = malloc(gob->num_images*sizeof(int));
	gob->height = malloc(gob->num_images*sizeof(int));
	gob->hs_x = malloc(gob->num_images*sizeof(int));
	gob->hs_y = malloc(gob->num_images*sizeof(int));
	gob->data = malloc(gob->num_images*sizeof(void *));
	gob->orig_data = malloc(gob->num_images*sizeof(void *));
	for (i=0; i<gob->num_images; i++) {
		int image_size;
		int offset;

		offset = (gob_data[i*4+2]) + (gob_data[i*4+3] << 8) + (gob_data[i*4+4] << 16) + (gob_data[i*4+5] << 24);

		gob->width[i]  = (short)((gob_data[offset]) + (gob_data[offset+1] << 8)); offset += 2;
		gob->height[i] = (short)((gob_data[offset]) + (gob_data[offset+1] << 8)); offset += 2;
		gob->hs_x[i]   = (short)((gob_data[offset]) + (gob_data[offset+1] << 8)); offset += 2;
		gob->hs_y[i]   = (short)((gob_data[offset]) + (gob_data[offset+1] << 8)); offset += 2;

		image_size = gob->width[i] * gob->height[i];
		gob->orig_data[i] = malloc(image_size);
		memcpy(gob->orig_data[i], &gob_data[offset], image_size);
		gob->data[i] = (unsigned short *)gob->orig_data[i];
	}
	free(gob_data);
	return 0;
}
