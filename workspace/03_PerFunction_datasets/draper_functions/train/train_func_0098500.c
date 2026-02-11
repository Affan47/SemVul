channel_complete_callback(int chan)
{
	Mix_Chunk *done_chunk = Mix_GetChunk(chan);
	Uint8 *chunkbuf=NULL;


	if(done_chunk->allocated == 0)
		chunkbuf = done_chunk->abuf;

	Mix_FreeChunk(done_chunk);


	if(chunkbuf)
		delete[] chunkbuf;
}
