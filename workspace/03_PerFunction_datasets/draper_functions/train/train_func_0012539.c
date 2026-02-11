mainInnCode() const
{

    for(int i=0; i < d_drug->m_Compo.count(); ++i) {
        IComponent *compo = d_drug->m_Compo.at(i);
        if (compo->isMainInn())
            return compo->data(IComponent::AtcId).toInt();
    }
    return -1;
}
