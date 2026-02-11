init_ray_bb()
{
	Square from, to, sq;

	for (int f=0; f<128; f++) {
		if (f & 0x88)
			continue;

		from = map0x88[f];

		for (int t=0; t<128; t++) {
			if (t & 0x88)
				continue;

			to = map0x88[t];

			ray_bb[from][to] = NULLBITBOARD;

			int dir;
			if (RNK(from) == RNK(to)
					&& FIL(from) < FIL(to)) {
				dir = 1;
			} else if (RNK(from) == RNK(to)
					&& FIL(from) > FIL(to)) {
				dir = -1;
			} else if (RNK(from) < RNK(to)
					&& FIL(from) == FIL(to)) {
				dir = 16;
			} else if (RNK(from) > RNK(to)
					&& FIL(from) == FIL(to)) {
				dir = -16;
			} else if (RNK(from) < RNK(to)
					&& FIL(from) < FIL(to)
					&& attack_bb[BISHOP][from]
							.testbit(to)) {
				dir = 17;
			} else if (RNK(from) < RNK(to)
					&& FIL(from) > FIL(to)
					&& attack_bb[BISHOP][from]
							.testbit(to)) {
				dir = 15;
			} else if (RNK(from) > RNK(to)
					&& FIL(from) < FIL(to)
					&& attack_bb[BISHOP][from]
							.testbit(to)) {
				dir = -15;
			} else if (RNK(from) > RNK(to)
					&& FIL(from) > FIL(to)
					&& attack_bb[BISHOP][from]
							.testbit(to)) {
				dir = -17;
			} else {
				continue;
			}

			int s = f+dir;
			while (s != t) {
				sq = map0x88[s];
				ray_bb[from][to].setbit(sq);
				s += dir;
			}
		}
	}
}
