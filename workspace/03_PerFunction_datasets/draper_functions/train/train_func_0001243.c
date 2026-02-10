ujfs_adjtree(int8_t * treep, int32_t l2leaves, int32_t l2min)
{
	int32_t nleaves, leaf_index, l2max, nextb, bsize, index;
	int32_t l2free, leaf, num_this_level, nextp;
	int8_t *cp0, *cp1, *cp = treep;


	nleaves = (1 << l2leaves);
	leaf_index = (nleaves - 1) / 3;


	l2max = l2min + l2leaves;


	for (l2free = l2min, bsize = 1; l2free < l2max; l2free++, bsize = nextb) {
		nextb = bsize << 1;

		for (cp0 = cp + leaf_index, index = 0; index < nleaves;
		     index += nextb, cp0 += nextb) {
			if (*cp0 == l2free && *(cp0 + bsize) == l2free) {
				*cp0 = l2free + 1;
				*(cp0 + bsize) = -1;
			}
		}
	}


	for (leaf = leaf_index, num_this_level = nleaves >> 2; num_this_level > 0;
	     num_this_level >>= 2, leaf = nextp) {
		nextp = (leaf - 1) >> 2;


		for (cp0 = cp + leaf, cp1 = cp + nextp, index = 0;
		     index < num_this_level; index++, cp0 += 4, cp1++) {
			*cp1 = TREEMAX(cp0);
		}
	}

	return (*cp);
}
