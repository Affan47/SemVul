resolveChildren()
{
    if (m_unresolvedChildren.empty()) {
        error() << "Type " << m_name << " has no unresolved children";
        return;
    }

    StringSet uchildren(m_unresolvedChildren);
    for (StringSet::const_iterator it = uchildren.begin(); it != uchildren.end(); ++it) {
        addChild(m_typeService->getTypeByName(*it));
    }

    assert(m_unresolvedChildren.empty());
}
