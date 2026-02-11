promptForBoolSeedAndNumTrials()
{
    if (clustalw::userParameters->getMenuFlag())
    {
        unsigned int tempSeed;
        tempSeed = clustalw::utilityObject->getInt(
                "\n\nEnter seed no. for random number generator ", 1, 1000,
        clustalw::userParameters->getBootRanSeed());
        clustalw::userParameters->setBootRanSeed(tempSeed);

        clustalw::userParameters->setBootNumTrials(
                     clustalw::utilityObject->getInt("\n\nEnter number of bootstrap trials ",
                        1, 10000, clustalw::userParameters->getBootNumTrials()));
    }
}
