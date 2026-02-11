printsextract_write_title(AjPFile inf, AjPFile outf, AjPStr *s)
{
    if(!ajReadlineTrim(inf,s))
	ajFatal("Premature EOF");

    if(!ajReadlineTrim(inf,s))
	ajFatal("Premature EOF");

    if(!ajStrPrefixC(*s,"gt;"))
	ajFatal("No title (%s)",ajStrGetPtr(*s));

    ajFmtPrintF(outf,"%s\n",ajStrGetPtr(*s)+4);

    return;
}
