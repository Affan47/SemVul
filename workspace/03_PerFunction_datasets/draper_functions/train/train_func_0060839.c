swapBytes(void *word, size_t size)
{
    union {
	boost::uint16_t s;
	struct {
	    boost::uint8_t c0;
	    boost::uint8_t c1;
	} c;
    } u;

    u.s = 1;
    if (u.c.c0 == 0) {

	return word;
    }


    boost::uint8_t *x = static_cast<boost::uint8_t *>(word);


    std::reverse(x, x+size);

    return word;
}
