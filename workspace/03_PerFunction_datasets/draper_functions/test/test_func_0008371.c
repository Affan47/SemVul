parse_if(int srclin, GLEPcode& pcode) throw(ParserError) {
	get_if(pcode);
	GLESourceBlock* block = add_block(GLE_SRCBLK_MAGIC+GLE_OPBEGIN_IF, srclin);
	block->setOffset2(pcode.size());
	pcode.addInt(0);
	pcode.addInt(0);
}
