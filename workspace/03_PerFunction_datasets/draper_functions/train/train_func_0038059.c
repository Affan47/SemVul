relatedContacts(const QString& relationshipType, QContactRelationship::Role role) const
{
    QList<QContactId> retn;
    for (int i = 0; i < d->m_relationshipsCache.size(); i++) {
        QContactRelationship curr = d->m_relationshipsCache.at(i);
        if (relationshipType.isEmpty() || curr.relationshipType() == relationshipType) {

            if (role == QContactRelationship::First) {
                if (curr.first() != d->m_id) {
                    if (!retn.contains(curr.first())) {
                        retn.append(curr.first());
                    }
                }
            } else if (role == QContactRelationship::Second) {
                if (curr.first() == d->m_id) {
                    if (!retn.contains(curr.second())) {
                        retn.append(curr.second());
                    }
                }
            } else {
                if (curr.first() == d->m_id) {
                    if (!retn.contains(curr.second())) {
                        retn.append(curr.second());
                    }
                } else {
                    if (!retn.contains(curr.first())) {
                        retn.append(curr.first());
                    }
                }
            }
        }
    }

    return retn;
}
