message(const DrugInteractionInformationQuery &query) const
    {
        Q_UNUSED(query);
        if (!m_Result->testedDrugs().isEmpty())
            return QString();
        return QString();
    }
