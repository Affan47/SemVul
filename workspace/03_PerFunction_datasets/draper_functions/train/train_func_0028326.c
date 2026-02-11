index_printflags(struct index_state *state,
			     uint32_t msgno, int usinguid)
{
    struct index_map *im = &state->map[msgno-1];

    index_fetchflags(state, msgno);


    if (usinguid || state->qresync)
	prot_printf(state->out, " UID %u", im->record.uid);
    if (state->qresync)
	prot_printf(state->out, " MODSEQ (" MODSEQ_FMT ")", im->record.modseq);
    prot_printf(state->out, ")\r\n");
}
