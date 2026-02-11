WriteApplicationColours()
{
    if (m_ChangedAppColours.empty())
        return;

    ColourManager *manager = Manager::Get()->GetColourManager();
    for (std::map<wxString, wxColour>::const_iterator it = m_ChangedAppColours.begin();
         it != m_ChangedAppColours.end();
         ++it)
    {
        manager->SetColour(it->first, it->second);
    }
}
