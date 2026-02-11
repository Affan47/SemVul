kStrCpy(state_t *s, int funct_nr, int argc, reg_t *argv)
{
	char *dest = (char *) kernel_dereference_bulk_pointer(s, argv[0], 0);
	char *src = (char *) kernel_dereference_bulk_pointer(s, argv[1], 0);

	if (!dest) {
		SCIkdebug(SCIkWARNING, "Attempt to strcpy TO invalid pointer "PREG"!\n",
			  PRINT_REG(argv[0]));
		return NULL_REG;
	}
	if (!src) {
		SCIkdebug(SCIkWARNING, "Attempt to strcpy FROM invalid pointer "PREG"!\n",
			  PRINT_REG(argv[1]));
		return NULL_REG;
	}

	if (argc > 2)
	{
		int length = SKPV(2);

		if (length>=0)
			strncpy(dest, src, length);
		else {
			if (s->seg_manager.heap[argv[0].segment]->type == MEM_OBJ_DYNMEM) {
				reg_t *srcp = (reg_t *) src;

				int i;
				SCIkdebug(SCIkWARNING, "Performing reg_t to raw conversion for AvoidPath\n");
				for (i = 0; i < -length / 2; i++) {
					dest[2 * i] = srcp->offset & 0xff;
					dest[2 * i + 1] = srcp->offset >> 8;
					srcp++;
				}
			} else
				memcpy(dest, src, -length);
		}
	}
	else
		strcpy(dest, src);

	return argv[0];
}
