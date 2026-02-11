scan_write(void * data, struct rc_instruction * inst,
		rc_register_file file, unsigned int index, unsigned int chan)
{
	struct schedule_state * s = data;
	struct reg_value ** pv = get_reg_valuep(s, file, index, chan);
	struct reg_value * newv;

	if (!pv)
		return;

	DBG("%i: write %i[%i] chan %i\n", s->Current->Instruction->IP, file, index, chan);

	newv = memory_pool_malloc(&s->C->Pool, sizeof(*newv));
	memset(newv, 0, sizeof(*newv));

	newv->Writer = s->Current;

	if (*pv) {
		(*pv)->Next = newv;
		s->Current->NumDependencies++;


		s->PrevWriter[chan] = (*pv)->Writer;
	}

	*pv = newv;

	if (s->Current->NumWriteValues >= 4) {
		rc_error(s->C, "%s: NumWriteValues overflow\n", __FUNCTION__);
	} else {
		s->Current->WriteValues[s->Current->NumWriteValues++] = newv;
	}
}
