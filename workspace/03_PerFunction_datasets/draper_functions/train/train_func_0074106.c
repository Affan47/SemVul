SetKeyBool(string SectionName, string KeyName, bool KeyBool)
{
    if (KeyBool)
    {
        return SetKeyString(SectionName, KeyName, "true");
    }
    else
    {
        return SetKeyString(SectionName, KeyName, "false");
    }
}
