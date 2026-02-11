NetStrTokenize(string in_str, string in_split,
										int return_partial) {
	return BaseStrTokenize(in_str, in_split, "\001");
}
