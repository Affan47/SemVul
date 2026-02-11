load(ObjectStream &f)
{
	bfdif = new BFDInterface;
	Disassembler::load(f);
}
