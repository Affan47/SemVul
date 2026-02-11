fitsbin_write_items_to(fitsbin_chunk_t* chunk, void* data, int N, FILE* fid) {
	if (fwrite(data, chunk->itemsize, N, fid) != N) {
		SYSERROR("Failed to write %i items", N);
		return -1;
	}
    return 0;
}
