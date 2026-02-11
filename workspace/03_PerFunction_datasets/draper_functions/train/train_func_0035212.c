addNeutralPlanetSomewhere(Player *neutral)
{
    Sector *sector = findRandomFreeSector();
    if (!sector)
        return NULL;
    return Planet::createNeutralPlanet(sector, neutral, UniquePlanetName());
}
