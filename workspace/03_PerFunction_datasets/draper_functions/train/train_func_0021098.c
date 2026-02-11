sightPerson(const AtlasAccount &ac)
{
    IdPersonMap::iterator P = m_people.find(ac->getId());
    if (P == m_people.end()) {
        error() << "got un-requested sight of person " << ac->getId();
        return;
    }

    if (P->second)
        P->second->sight(ac);
    else {

        P->second = new Person(this, ac);
    }


    SightPerson.emit(P->second);
}
