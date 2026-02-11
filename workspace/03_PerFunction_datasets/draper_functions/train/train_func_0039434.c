item(unsigned index)
{
    if (index >= (unsigned int) m_contents->count())
        return 0;

    return m_contents->at(index);
}
