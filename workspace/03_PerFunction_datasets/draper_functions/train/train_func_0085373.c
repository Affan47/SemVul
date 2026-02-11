mt9m032_row_time(struct mt9m032 *sensor, unsigned int width)
{
	unsigned int effective_width;
	u32 ns;

	effective_width = width + 716;
	ns = div_u64(1000000000ULL * effective_width, sensor->pix_clock);
	dev_dbg(to_dev(sensor),	"MT9M032 line time: %u ns\n", ns);
	return ns;
}
