write_u32_portable(FILE* fout, unsigned int val) {
    uint32_t v = htonl((uint32_t)val);
    if (fwrite(&v, 4, 1, fout) == 1) {
		return 0;
    } else {
		fprintf(stderr, "Couldn't write u32: %s\n", strerror(errno));
		return 1;
    }
}
