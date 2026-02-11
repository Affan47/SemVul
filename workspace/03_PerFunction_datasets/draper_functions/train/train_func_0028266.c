isNear(int instance, int other, bool directly)
{
    Aint l1, l2;

    verifyInstance(instance, "NEAR");

    if (isALocation(instance))
        l1 = instance;
    else
        l1 = where(instance, directly);
    if (isALocation(other))
        l2 = other;
    else
        l2 = where(other, directly);
    return exitto(l2, l1);
}
