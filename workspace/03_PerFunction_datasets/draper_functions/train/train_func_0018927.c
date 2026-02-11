gen_stack(CharstringInterp &interp, int for_cmd)
{
    const char *str = ((unsigned)for_cmd <= Charstring::cLastCommand ? command_desc[for_cmd] : (const char *)0);
    if ((for_cmd == Charstring::cHstem3 || for_cmd == Charstring::cVstem3)
	&& gen_stem3_stack(interp))
	return;

    int i;
    for (i = 0; str && *str && i < interp.size(); i++, str++)
	gen_number(interp.at(i), *str);
    for (; i < interp.size(); i++)
	gen_number(interp.at(i));
    interp.clear();
}
