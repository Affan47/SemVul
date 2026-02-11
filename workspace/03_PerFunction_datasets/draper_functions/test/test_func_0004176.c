HandleLookupSpellCommand(char* args)
{
    if (!*args)
        { return false; }


    Player* target = getSelectedPlayer();

    std::string namepart = args;
    std::wstring wnamepart;

    if (!Utf8toWStr(namepart, wnamepart))
        { return false; }


    wstrToLower(wnamepart);

    uint32 counter = 0;


    for (uint32 id = 0; id < sSpellStore.GetNumRows(); ++id)
    {
        SpellEntry const* spellInfo = sSpellStore.LookupEntry(id);
        if (spellInfo)
        {
            int loc = GetSessionDbcLocale();
            std::string name = spellInfo->SpellName[loc];
            if (name.empty())
                { continue; }

            if (!Utf8FitTo(name, wnamepart))
            {
                loc = 0;
                for (; loc < MAX_LOCALE; ++loc)
                {
                    if (loc == GetSessionDbcLocale())
                        { continue; }

                    name = spellInfo->SpellName[loc];
                    if (name.empty())
                        { continue; }

                    if (Utf8FitTo(name, wnamepart))
                        { break; }
                }
            }

            if (loc < MAX_LOCALE)
            {
                ShowSpellListHelper(target, spellInfo, LocaleConstant(loc));
                ++counter;
            }
        }
    }
    if (counter == 0)
        { SendSysMessage(LANG_COMMAND_NOSPELLFOUND); }
    return true;
}
