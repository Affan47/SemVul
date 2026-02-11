locate_inst(const uint8_t** code,  int* codeLen, _OffsetType* codeOffset, _WString* instructionHex, _PrefixState* ps, _DecodeType dt)
{
	_InstInfo* ii = NULL;

	unsigned int lastCodeLen = *codeLen;
	_OffsetType lastCodeOffset = *codeOffset;
	const uint8_t* lastCode = *code;

	unsigned int lastBC = 0;


	if (ps->start < ps->last) {


		if (ps->isREXPrefixValid && (ps->start <= ps->last - 2)) lastBC = *(ps->last - 2);
		else lastBC = *(ps->last-1);
	}


	if ((lastBC == PREFIX_REP) || (lastBC == PREFIX_REPNZ) || (lastBC == PREFIX_OP_SIZE)) {

		if (ps->isREXPrefixValid) {
			(*code) -= 2;
			(*codeLen) += 2;
			(*codeOffset) -= 2;
		} else {
			(*code)--;
			(*codeLen)++;
			(*codeOffset)--;
		}
		ii = locate_raw_inst(code, codeLen, codeOffset, instructionHex, ps->isREXPrefixValid, dt);
		if (ii) {


			if (ps->isREXPrefixValid) {
				ps->last -= 2;
				ps->specialPrefixesSize = 2;
			}
			else {
				ps->last--;
				ps->specialPrefixesSize = 1;
			}


			switch (lastBC)
			{
				case PREFIX_REP: ps->totalPrefixes &= ~INST_PRE_LOKREP_MASK; ps->lokrepPos = NULL; break;
				case PREFIX_REPNZ: ps->totalPrefixes &= ~INST_PRE_LOKREP_MASK; ps->lokrepPos = NULL; break;
				case PREFIX_OP_SIZE: ps->totalPrefixes &= ~INST_PRE_OP_SIZE; ps->opsizePos = NULL; break;
			}
		} else {

			strclear_WS(instructionHex);
			*code = lastCode;
			*codeLen = lastCodeLen;
			*codeOffset = lastCodeOffset;
		}
	}

	if (ii == NULL) ii = locate_raw_inst(code, codeLen, codeOffset, instructionHex, 0, dt);
	return ii;
}
