freeMixer() {
	if (enabled) {
		Mix_ExpireChannel(-1, 0);
		for (unsigned int index = 0; index < mixChunks.size(); index++) {
			Mix_FreeChunk(mixChunks[index]);
		}
		for (unsigned int index = 0; index < musics.size(); index++) {
			Mix_FreeMusic(musics[index]);
		}
	}
}
