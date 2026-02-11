Inverse(const Integer &a) const
{
	if (!a)
		return a;

	CopyWords(m_result.reg.begin(), m_modulus.reg, m_modulus.reg.size());
	if (CryptoPP::Subtract(m_result.reg.begin(), m_result.reg, a.reg, a.reg.size()))
		Decrement(m_result.reg.begin()+a.reg.size(), m_modulus.reg.size()-a.reg.size());

	return m_result;
}
