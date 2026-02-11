appendSubstring(RenderedString& rs,
                     const String& string,
                     Font* initial_font,
                     const ColourRect* initial_colours)
{
    RenderedStringTextComponent rstc(string, initial_font);

    if (initial_colours)
        rstc.setColours(*initial_colours);

    rs.appendComponent(rstc);
}
