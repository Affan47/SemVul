AutoComplete(cbEditor& ed)
{
    if (Abbreviations::Get())
        Abbreviations::Get()->DoAutoComplete(&ed);
}
