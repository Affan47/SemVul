GetPSFonts () {
    if (_fonts == nil) {
        _fonts = new UList;

        CollectFontsFromGraphic(GetGraphicComp()->GetGraphic(), _fonts);
    }
    return _fonts;
}
