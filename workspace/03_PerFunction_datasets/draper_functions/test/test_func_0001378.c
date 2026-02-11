linkWithComposition(IComponent *link)
{
    Q_ASSERT(link);
    d_component->m_Link = link;
    if (!link->isLinkedWith(this)) {
        link->linkWithComposition(this);
        bool active = (data(Nature).toString()=="SA");
        setDataFromDb(IsActiveSubstance, active);
        link->setIsActiveSubstance(!active);
    }
}
