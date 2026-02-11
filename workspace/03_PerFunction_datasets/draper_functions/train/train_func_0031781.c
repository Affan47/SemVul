getUpgrader(const SbName &className, float version)


{

    if (version != 1.0 && version != 2.0) return NULL;


    void *t;
    if (! getUpgradeDict(version)->find((unsigned long) className.getString(), t))
	return NULL;

    SoType *type = (SoType *) t;

    return (SoUpgrader *)type->createInstance();
}
