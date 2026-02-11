qHash(const QContactRelationship &key)
{
    return qHash(key.first()) + qHash(key.second())
        + QT_PREPEND_NAMESPACE(qHash)(key.relationshipType());
}
