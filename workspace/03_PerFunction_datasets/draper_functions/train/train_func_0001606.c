load_rax(void* value) {
	EnsureSpace ensure_space(this);
	emit(0x48);
	emit(0xA1);
	emitq(reinterpret_cast<uintptr_t> (value));
}
