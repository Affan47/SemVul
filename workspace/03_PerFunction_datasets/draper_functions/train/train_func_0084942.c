excel_unexpected_biff (BiffQuery *q, char const *state,
		       int debug_level)
{
#ifndef NO_DEBUG_EXCEL
	if (debug_level > 1) {
		g_print ("Unexpected Opcode in %s: 0x%hx, length 0x%x\n",
			 state, q->opcode, q->length);
		if (debug_level > 2)
			gsf_mem_dump (q->data, q->length);
	}
#endif
}
