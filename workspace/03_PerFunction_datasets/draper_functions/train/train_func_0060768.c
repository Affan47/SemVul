DeKey()
{
	FixedSizeSecBlock<IDEA::Word, 6*ROUNDS+4> tempkey;
	size_t i;

	for (i=0; i<ROUNDS; i++)
	{
		tempkey[i*6+0] = MulInv(m_key[(ROUNDS-i)*6+0]);
		tempkey[i*6+1] = AddInv(m_key[(ROUNDS-i)*6+1+(i>0)]);
		tempkey[i*6+2] = AddInv(m_key[(ROUNDS-i)*6+2-(i>0)]);
		tempkey[i*6+3] = MulInv(m_key[(ROUNDS-i)*6+3]);
		tempkey[i*6+4] =        m_key[(ROUNDS-1-i)*6+4];
		tempkey[i*6+5] =        m_key[(ROUNDS-1-i)*6+5];
	}

	tempkey[i*6+0] = MulInv(m_key[(ROUNDS-i)*6+0]);
	tempkey[i*6+1] = AddInv(m_key[(ROUNDS-i)*6+1]);
	tempkey[i*6+2] = AddInv(m_key[(ROUNDS-i)*6+2]);
	tempkey[i*6+3] = MulInv(m_key[(ROUNDS-i)*6+3]);

	m_key = tempkey;
}
