macro_replay(const Arg *arg) {
	Macro *macro = key2macro(arg);
	if (!macro || macro == vis->recording)
		return;
	for (size_t i = 0; i < macro->len; i += sizeof(Key))
		keypress((Key*)(macro->data + i));
}
