parse(const DocumentSource& source) const
{
    QDomDocument doc = source.asDomDocument();

    if (doc.isNull())
        return Syndication::SpecificDocumentPtr(new Document());

    doc = d->addEnumeration(doc);

    ModelMaker maker;
    Model model = maker.createFromXML(doc);

    bool is09 = !model.resourcesWithType(RSS09Vocab::self()->channel()).isEmpty();

    if (is09)
    {
        d->map09to10(model);
        d->addSequenceFor09(model);
    }

    QList<ResourcePtr> channels = model.resourcesWithType(RSSVocab::self()->channel());

    if (channels.isEmpty())
        return Syndication::SpecificDocumentPtr(new Document());

    return DocumentPtr(new Document(*(channels.begin())));
}
