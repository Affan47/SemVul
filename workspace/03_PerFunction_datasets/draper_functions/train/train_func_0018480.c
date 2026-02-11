WriteReg(unsigned int reg, unsigned int val)
{
    int i;


    if ((reg & 0xf0) == OPL_REGS_FEEDBACK)
    {
        val |= 0x30;
    }

    OPL_WritePort(OPL_REGISTER_PORT, reg);

    for (i=0; i<6; ++i)
    {
        OPL_ReadPort(OPL_REGISTER_PORT);
    }

    OPL_WritePort(OPL_DATA_PORT, val);

    for (i=0; i<35; ++i)
    {
        OPL_ReadPort(OPL_REGISTER_PORT);
    }
}
