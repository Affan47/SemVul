resize(uint previousSize, uint newSize)
{
    Q_ASSERT(previousSize == m_chain.size());
    m_chain.resize(newSize);

    if (newSize >= previousSize) {

        for (uint i = previousSize; i < newSize; ++i) {
            m_chain[i] = i + 1;
        }
    } else {


        for (int i = 0; i < m_chain.size(); ++i) {
            m_chain[i] = qMin(m_chain[i], newSize);
        }
    }
}
