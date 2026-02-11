Read (istream& in) {
    GraphicComp::Read(in);
    int lineHt;

    in >> lineHt;
    char* string = ReadString(in);
    TextGraphic* text = new TextGraphic(string, lineHt);
    delete[] string;

    text->FillBg(ReadBgFilled(in));
    PSColor* fg = ReadColor(in);
    PSColor* bg = ReadColor(in);
    text->SetColors(fg, bg);
    text->SetFont(ReadFont(in));

    Transformer* t = ReadTransformer(in);
    text->SetTransformer(t);
    Unref(t);

    SetGraphic(text);
}
