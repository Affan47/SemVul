placeInRegister(Operand r) {
	if(r.loc != REGISTER && r.loc != INVALID) {
		kill(r);
		Operand t = allocRegister();
		emit(ByteCode::fastmov, r, 0, t);
		return t;
	}
	return r;
}
