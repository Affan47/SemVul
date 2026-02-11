doRandom(float *buffer, int nFrames)
{
    register int period = (int) (rate / freq);
    for (int i = 0; i < nFrames; i++) {
	if (random_count > period) {
	    random_count = 0;
		random = randf();
	}
	random_count++;
	buffer[i] = random;
    }
}
