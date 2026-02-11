Validate()
{
    if (2 == numConsts &&
        cc[0].reg.bits.name == cc[1].reg.bits.name)
        errors.set("global constant set twice");

    generals.Validate(numConsts, &cc[0]);

    final.Validate();
}
