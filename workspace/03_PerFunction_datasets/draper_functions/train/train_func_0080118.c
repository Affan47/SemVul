compute_positions_as_predecessor(struct compilation_unit *cu)
{
	struct basic_block *bb;

	for_each_basic_block(bb, &cu->bb_list) {
		if (bb_is_eh(cu, bb))
			continue;

		bb->positions_as_predecessor = malloc(bb->nr_successors * sizeof(unsigned long));
		if (!bb->positions_as_predecessor)
			return warn("out of memory"), -ENOMEM;

		for (unsigned long i = 0; i < bb->nr_successors; i++) {
			struct basic_block *succ = bb->successors[i];
			unsigned long position;

			position = 0;
			for (unsigned long j = 0; j < succ->nr_predecessors; j++) {
				struct basic_block *pred = succ->predecessors[j];
				if (bb_is_eh(cu, pred))
					continue;

				if (pred == bb) {
					bb->positions_as_predecessor[i] = position;
					break;
				}

				position++;
			}
		}
	}

	return 0;
}
