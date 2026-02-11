assign(const QOrganizerItemDetail& other, const char* expectedDefinitionId)
{
    if (this != &other) {
        if (other.d->m_definitionName == expectedDefinitionId) {
            d = other.d;
        } else {
            d = new QOrganizerItemDetailPrivate;
            d->m_definitionName = expectedDefinitionId;
        }
    }
    return *this;
}
