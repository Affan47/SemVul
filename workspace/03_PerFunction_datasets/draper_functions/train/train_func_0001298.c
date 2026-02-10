enableLanguages (const boolean state)
{
    unsigned int i;
    for (i = 0  ;  i < LanguageCount  ;  ++i)
	LanguageTable [i]->enabled = state;
}
