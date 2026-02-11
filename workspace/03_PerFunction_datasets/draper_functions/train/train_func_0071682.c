Get(int nIndex)
{
    if (nIndex < 0 || nIndex >= GetLength())
        return NULL;
    return m_array[nIndex];
}
