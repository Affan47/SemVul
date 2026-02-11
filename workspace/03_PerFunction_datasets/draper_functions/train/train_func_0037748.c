EnvironmentName(CommandArray *code)
{
    if (code == PreambleCommands)
        return strdup("preamble");
    if (code == commands)
        return strdup("document");
    if (code == ItemizeCommands)
        return strdup("itemize");
    if (code == EnumerateCommands)
        return strdup("enumerate");
    if (code == DescriptionCommands)
        return strdup("description");
    if (code == InparaenumCommands)
        return strdup("inparaenum");
    if (code == LetterCommands)
        return strdup("letter");
    if (code == GermanModeCommands)
        return strdup("german");
    if (code == FrenchModeCommands)
        return strdup("french");
    if (code == RussianModeCommands)
        return strdup("russian");
    if (code == CzechModeCommands)
        return strdup("czech");
    if (code == FigureCommands)
        return strdup("figure or wrapfigure");
    if (code == ignoreCommands)
        return strdup("unknown environment");
    if (code == hyperlatexCommands)
        return strdup("hyperlatex");
    if (code == apaciteCommands)
        return strdup("apacite");
    if (code == natbibCommands)
        return strdup("natbib");
    if (code == harvardCommands)
        return strdup("harvard");
    if (code == authordateCommands)
        return strdup("authordate");
    if (code == verbatimCommands)
        return strdup("verbatim");
    if (code == quoteCommands)
        return strdup("quote");
    if (code == quotationCommands)
        return strdup("quotation");
    if (code == bibliographyCommands)
        return strdup("bibliography");
    if (code == verseCommands)
        return strdup("verse");
    if (code == genericCommands)
        return strdup("generic");
    if (code == acronymCommands)
        return strdup("acronym");
    if (code == spacingCommands)
        return strdup("setpace");
    return strdup("unknown");
}
