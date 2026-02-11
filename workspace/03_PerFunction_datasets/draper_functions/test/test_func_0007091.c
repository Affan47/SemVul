exists() const
{
    for (int i = 0; i < 2; i++) {
        for (int e = 0; e < 3; e++) {
            if (m_nodes[i][e] &&
                m_nodes[i][e]->exists()) {
                return true;
            }
        }
    }
    return false;
}
