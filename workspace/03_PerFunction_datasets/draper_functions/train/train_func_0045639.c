get_block_size(int w, int h, int mode, int min)
{
    int max = MAX(MAX(w, h), min);
    int bits = number_of_bits(max);

    if (mode == EPS_MODE_NORMAL) {

        if (max == (1 << (bits - 1))) {
            return max;
        } else {
            return (1 << bits);
        }
    } else {

        if (max == (1 << (bits - 1)) + 1) {
            return max;
        } else if (max == (1 << (bits - 1))) {
            return max + 1;
        } else {
            return (1 << bits) + 1;
        }
    }
}
