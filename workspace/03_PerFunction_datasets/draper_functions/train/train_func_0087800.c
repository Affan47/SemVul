getViewOrientation() const
{
    WFMath::Quaternion vor;

	vor.identity();
    for (const Entity* e = this; e; e = e->getLocation())
        vor *= e->getOrientation();

    return vor;
}
