clear_last() {
    int m = _max;
    if (m < 0)
	_data[0] = 0;
    else if ((m & wmask) != wmask) {
	word_type mask = (word_type(1) << ((m & wmask) + 1)) - 1;
	_data[m >> wshift] &= mask;
    }
}
