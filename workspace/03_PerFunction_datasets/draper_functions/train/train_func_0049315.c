alloc_node(const char* file)
{
	FILE_LIST* node;

	node = calloc(1, sizeof(*node));

	if (node != NULL) {
		node->filename = strdup(file);

		if (node->filename != NULL) {
			node->track_peak = NO_PEAK;
			node->track_gain = NO_GAIN;
			node->dc_offset[0] = 0.;
			node->dc_offset[1] = 0.;
			node->offset[0] = 0.;
			node->offset[1] = 0.;
			return node;
		}
		free(node);
	}

	fprintf(stderr, _("Out of memory\n"));
	return NULL;
}
