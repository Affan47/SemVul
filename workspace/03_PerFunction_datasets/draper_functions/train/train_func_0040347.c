setPropertyList(QString name, Nodes nodes)
{
    Uri property = getPropertyUri(name);
    Triple t(m_node, property, Node());
    m_store->remove(t);
    for (int i = 0; i < nodes.size(); ++i) {
        t.c = nodes[i];
        m_store->add(t);
    }
}
