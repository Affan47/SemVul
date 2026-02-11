init()
{
	int i;


	for (i=0; i<65536; i++) {
		lsb_lut[i] = -1;
		for (int j=0; j<16; j++) {
			if (i & (1<<j)) {
				lsb_lut[i] = (int8_t) j;
				break;
			}
		}
	}


	for (i=0; i<65536; i++) {
		msb_lut[i] = -1;
		for (int j=15; j>=0; j--) {
			if (i & (1<<j)) {
				msb_lut[i] = (int8_t) j;
				break;
			}
		}
	}


	for (i=0; i<65536; i++) {
		popcnt_lut[i] = 0;
		for (int j=0; j<16; j++) {
			if (i & (1<<j))
				popcnt_lut[i]++;
		}
	}


	for (int f=0; f<8; f++) {
		file[f] = NULLBITBOARD;
		for (int r=0; r<8; r++) {
			file[f].setbit(SQUARE(r,f));
		}
	}


	for (int r=0; r<8; r++) {
		rank[r] = NULLBITBOARD;
		for (int f=0; f<8; f++) {
			rank[r].setbit(SQUARE(r,f));
		}
	}

	init_attack_bb();
	init_pawn_capt_bb();
	init_ray_bb();
	init_masks();
	init_rot_atk();
}
