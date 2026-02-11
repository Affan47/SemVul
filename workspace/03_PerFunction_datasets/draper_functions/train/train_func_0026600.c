Validate(int stage, int portion)
{
    int args = 1;

    if (RCP_DOT == op || RCP_MUL == op)
        args = 3;
    else
        args = 1;

    if (reg[0].reg.bits.readOnly)
        errors.set("writing to a read-only register");

    if (RCP_ALPHA == portion &&
        RCP_DOT == op)
        errors.set("dot used in alpha portion");
    int i;
    for (i = 0; i < args; i++) {
        ConvertRegister(reg[i].reg, portion);
        if (reg[i].reg.bits.finalOnly)
            errors.set("final register used in general combiner");
        if (RCP_RGB == portion &&
            RCP_BLUE == reg[i].reg.bits.channel)
            errors.set("blue register used in rgb portion");
        if (RCP_ALPHA == portion &&
            RCP_RGB == reg[i].reg.bits.channel)
            errors.set("rgb register used in alpha portion");
        if (i > 0 &&
            GL_DISCARD_NV == reg[i].reg.bits.name)
            errors.set("reading from discard");
    }
}
