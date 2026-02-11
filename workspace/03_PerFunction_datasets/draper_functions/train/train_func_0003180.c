findNULL()
{
	for (unsigned int i = 0; i < l.size(); i++) {
		if (l[i] == NULL) {
#ifdef DGDEBUG
			std::cout << "found free list:" << i << std::endl;
#endif
			return (signed) i;
		}
	}
	return -1;
}
