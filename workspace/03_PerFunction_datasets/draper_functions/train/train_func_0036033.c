DeleteLogger(Logger* l)
{
    if (!l)
        return false;

    for (size_t i = 0; i < m_Pages.GetCount(); ++i)
    {
        if (m_Pages.Item(i)->logger == l)
        {
            int index = Manager::Get()->GetLogManager()->FindIndex(l);
            if (index >= 0)
                Manager::Get()->GetLogManager()->DeleteLog(index);

            if (m_Pages.Item(i)->indexInNB >= 0)
                DeletePage(GetPageIndex(m_Pages.Item(i)->window));

            delete(m_Pages.Item(i));
            m_Pages.RemoveAt(i);
            return true;
        }
    }

   return false;
}
