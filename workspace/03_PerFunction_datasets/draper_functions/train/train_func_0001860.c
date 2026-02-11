find_keys(const uint8_t* bmap, size_t last)
{
    size_t percent = 0;
    const size_t increment = last / 100;

    if (gProgress)
        print_progress(percent);

    for (size_t i = 0; i < last; i++) {
        if (entropy(bmap,i)) continue;

        uint32_t* map = (uint32_t*)&(bmap[i]);


        int xor_count_256 = 0;
        for (size_t row = 1; row < 8; row++) {
            for (size_t column = 0; column < 8; column++) {
                if (row == 7 && column == 4) break;
                if (column == 0)
                    xor_count_256 += popcount(key_core(map[8*row-1],row) ^
                            map[8*(row-1)] ^
                            map[8*row]);
                else if (column == 4)
                    xor_count_256 += popcount(sbox_bytes(map[8*row+3])^
                            map[8*(row-1)+4] ^
                            map[8*row+4]);
                else
                    xor_count_256 += popcount(map[8*row+column-1] ^
                            map[8*(row-1)+column] ^
                            map[8*row + column]);
            }
	    if (xor_count_256 > gThreshold)
	      break;
        }
        if (xor_count_256 <= gThreshold)
            print_key(map,256,i);


        int xor_count_128 = 0;
        for (size_t row = 1; row < 11; row++) {
            for (size_t column = 0; column < 4; column++) {
                if (column == 0)
                    xor_count_128 += popcount(key_core(map[4*row-1],row) ^
                            map[4*(row-1)] ^
                            map[4*row]);
                else
                    xor_count_128 += popcount((map[4*row + column-1] ^
                            map[4*(row-1)+column]) ^
                            map[4*row + column]);
            }
	    if (xor_count_128 > gThreshold)
	      break;
        }
        if (xor_count_128 < gThreshold)
            print_key(map,128,i);

        if (gProgress) {
            size_t pct = (increment > 0) ? i / increment : i * 100 / last;
            if (pct > percent) {
                percent = pct;
                print_progress(percent);
            }
        }
    }

    if (gProgress) {
        print_progress(100);
        fprintf(stderr, "\n");
    }
}
