fromTableDirection(unsigned char dir, int local_neighbors)
{

	switch (dir) {
		case FS:
			return 0;
		case TLS:
			return (ANGLES / local_neighbors);
		case THLS:
			return (2 * ANGLES / local_neighbors);
		case TBS:
			return ((local_neighbors / 2) * ANGLES / local_neighbors);
		case THRS:
			return (ANGLES - 2 * ANGLES / local_neighbors);
		case TRS:
			return (ANGLES - ANGLES / local_neighbors);
		case SF:
			return ANGLES;
		case STL:
			return (ANGLES + ANGLES / local_neighbors);
		case STHL:
			return (ANGLES + 2 * ANGLES / local_neighbors);
		case STB:
			return (ANGLES + (local_neighbors / 2) * ANGLES / local_neighbors);
		case STHR:
			return (2 * ANGLES - 2 * ANGLES / local_neighbors);
		case STR:
			return (2 * ANGLES - ANGLES / local_neighbors);
		default:
			(void) fprintf(stderr, "wrong direction %d from table\n", dir);
	}
	return -1;
}
