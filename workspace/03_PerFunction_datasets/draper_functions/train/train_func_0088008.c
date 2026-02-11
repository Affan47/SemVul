ctlr_bcopy(int baddr_from, int baddr_to, int count, int move_ea)
{

	if (memcmp((char *) &ea_buf[baddr_from],
	           (char *) &ea_buf[baddr_to],
		   count * sizeof(struct ea))) {
		(void) memmove(&ea_buf[baddr_to], &ea_buf[baddr_from],
			           count * sizeof(struct ea));
		REGION_CHANGED(baddr_to, baddr_to + count);


		if (area_is_selected(baddr_to, count))
			unselect(baddr_to, count);
	}

}
