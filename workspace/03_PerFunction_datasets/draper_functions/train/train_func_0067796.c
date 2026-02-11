initClass()


{
    SO__NODE_INIT_ABSTRACT_CLASS(SoUpgrader, "Upgrader", SoGroup);

    classTypeId.makeInternal();
    upgradeDictV1 = new SbDict(50);
    upgradeDictV2 = new SbDict(10);
}
