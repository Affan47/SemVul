infereDocConstantTblType(Type size, Type init)
{
    checkKonst(checkInt(checkInit(size)));

    return init;
}
