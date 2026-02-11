defends(int adtyp, struct obj *otmp)
{
    const struct artifact *weap = get_artifact(otmp);
    return (weap && (weap->defn.adtyp == adtyp));
}
