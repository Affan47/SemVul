emit_byte(Byte b, State * state)
{
    if (state->num_bytes == state->max_bytes) {
	unsigned new_max = 2 * state->max_bytes;
	state->bytes = myrealloc(state->bytes, sizeof(Byte) * new_max,
				 M_BYTECODES);
#ifdef BYTECODE_REDUCE_REF
	state->pushmap = myrealloc(state->pushmap, sizeof(Byte) * new_max,
				   M_BYTECODES);
	state->trymap = myrealloc(state->trymap, sizeof(Byte) * new_max,
				  M_BYTECODES);
#endif
	state->max_bytes = new_max;
    }
#ifdef BYTECODE_REDUCE_REF
    state->pushmap[state->num_bytes] = 0;
    state->trymap[state->num_bytes] = state->try_depth;
#endif
    state->bytes[state->num_bytes++] = b;
}
