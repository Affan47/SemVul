ioc_iswhole(unsigned int major, unsigned int minor)
{
	if (!ioc_parsed && !ioc_init())
		return 0;

	if (major >= MAX_BLKDEV)


		return 0;

	if (ioconf[major] == NULL)

		return 0 ;

	return (IS_WHOLE(major, minor));
}
