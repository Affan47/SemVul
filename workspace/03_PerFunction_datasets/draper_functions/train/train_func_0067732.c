cloneNode ( bool deep )
{
    WTF::RefPtr<ElementImpl> clone = new XMLElementImpl(docPtr(), NamespaceName::fromId(namespacePart(id())), LocalName::fromId(localNamePart(id())), m_prefix);
    finishCloneNode( clone.get(), deep );
    return clone;
}
