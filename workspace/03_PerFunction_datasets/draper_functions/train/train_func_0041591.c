joiner_destroy (joiner *jr)
{
    if (jr != NULL) {
	free(jr->rows);
	free(jr->keys);
	free(jr->key_freq);
	free(jr->key_row);
	free(jr);
    }
}
