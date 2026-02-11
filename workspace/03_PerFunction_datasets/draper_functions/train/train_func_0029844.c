bmz_dump(cmph_t *mphf, FILE *fd)
{
	char *buf = NULL;
	cmph_uint32 buflen;
	cmph_uint32 two = 2;
	bmz_data_t *data = (bmz_data_t *)mphf->data;
	register size_t nbytes;
#ifdef DEBUG
	cmph_uint32 i;
#endif

	__cmph_dump(mphf, fd);

	nbytes = fwrite(&two, sizeof(cmph_uint32), (size_t)1, fd);

	hash_state_dump(data->hashes[0], &buf, &buflen);
	DEBUGP("Dumping hash state with %u bytes to disk\n", buflen);
	nbytes = fwrite(&buflen, sizeof(cmph_uint32), (size_t)1, fd);
	nbytes = fwrite(buf, (size_t)buflen, (size_t)1, fd);
	free(buf);

	hash_state_dump(data->hashes[1], &buf, &buflen);
	DEBUGP("Dumping hash state with %u bytes to disk\n", buflen);
	nbytes = fwrite(&buflen, sizeof(cmph_uint32), (size_t)1, fd);
	nbytes = fwrite(buf, (size_t)buflen, (size_t)1, fd);
	free(buf);

	nbytes = fwrite(&(data->n), sizeof(cmph_uint32), (size_t)1, fd);
	nbytes = fwrite(&(data->m), sizeof(cmph_uint32), (size_t)1, fd);

	nbytes = fwrite(data->g, sizeof(cmph_uint32)*(data->n), (size_t)1, fd);
	if (nbytes == 0 && ferror(fd)) {
          fprintf(stderr, "ERROR: %s\n", strerror(errno));
          return 0;
        }
	#ifdef DEBUG
	fprintf(stderr, "G: ");
	for (i = 0; i < data->n; ++i) fprintf(stderr, "%u ", data->g[i]);
	fprintf(stderr, "\n");
	#endif
	return 1;
}
