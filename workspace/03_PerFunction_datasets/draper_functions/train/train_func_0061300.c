describe(int instance)
{
    bool descriptionOk;
    int previousInstance = current.instance;

    current.instance = instance;
    verifyInstance(instance, "DESCRIBE");
    if (descriptionCheck(instance)) {
        descriptionOk = TRUE;
        if (isObject(instance)) {
            describeObject(instance);
        } else if (isActor(instance)) {
            describeActor(instance);
        } else
            describeAnything(instance);
    } else
        descriptionOk = FALSE;
    current.instance = previousInstance;
    return descriptionOk;
}
