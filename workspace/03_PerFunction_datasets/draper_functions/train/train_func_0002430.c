reverseComplement()
{
    this->reverse();
    for(size_t idx = 0; idx < m_len; ++idx) m_data[idx] = complement(m_data[idx]);
}
