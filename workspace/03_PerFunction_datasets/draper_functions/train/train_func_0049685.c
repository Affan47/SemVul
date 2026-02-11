ensAttributeNewIni(EnsPAttributetype at,
                                 AjPStr value)
{
    EnsPAttribute attribute = NULL;

    AJNEW0(attribute);

    attribute->Attributetype = ensAttributetypeNewRef(at);

    if (value)
        attribute->Value = ajStrNewRef(value);

    attribute->Use = 1U;

    return attribute;
}
