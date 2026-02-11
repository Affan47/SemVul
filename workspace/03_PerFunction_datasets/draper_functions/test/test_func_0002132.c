bdelta_pass(BDelta_Instance *b, unsigned blocksize, unsigned minMatchSize, unsigned maxHoleSize, unsigned flags) {

	b->matches.push_back(Match(b->data1_size, b->data2_size, 0));

	UnusedRange *unused = new UnusedRange[b->matches.size() + 1],
			    *unused2 = new UnusedRange[b->matches.size() + 1];
	unsigned numunused = 0, numunused2 = 0;
	for (std::list<Match>::iterator l = b->matches.begin(); l != b->matches.end(); ++l) {
		unused[numunused++] = UnusedRange(l->p1, l->num, l, l);
		unused2[numunused2++] = UnusedRange(l->p2, l->num, l, l);
	}

	std::sort(unused, unused + numunused, comparep);


	get_unused_blocks(unused, &numunused);

	get_unused_blocks(unused2, &numunused2);


	if (flags & BDELTA_GLOBAL)
		bdelta_pass_2(b, blocksize, minMatchSize, unused, numunused, unused2, numunused2);
	else {
		std::sort(unused, unused + numunused, comparemrp2);
		for (unsigned i = 0; i < numunused; ++i) {
			UnusedRange u1 = unused[i], u2 = unused2[i];
			if (u1.num >= blocksize && u2.num >= blocksize)
				if (! maxHoleSize || (u1.num <= maxHoleSize && u2.num <= maxHoleSize))
					if (! (flags & BDELTA_SIDES_ORDERED) || (next(u1.ml) == u1.mr))
						bdelta_pass_2(b, blocksize, minMatchSize, &u1, 1, &u2, 1);
		}
	}

	if (verbose) printf("pass (blocksize: %d, matches: %zu)\n", blocksize, b->matches.size());


	b->matches.pop_back();

	delete [] unused;
	delete [] unused2;
}
