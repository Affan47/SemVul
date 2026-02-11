Read (istream& in) {
    GraphicComp::Read(in);
    Coord x0, y0, x1, y1;

    in >> x0 >> y0 >> x1 >> y1;
    SF_Rect* rect = new SF_Rect(x0, y0, x1, y1);

    rect->FillBg(ReadBgFilled(in));
    PSColor* fg = ReadColor(in);
    PSColor* bg = ReadColor(in);
    rect->SetColors(fg, bg);
    rect->SetBrush(ReadBrush(in));
    rect->SetPattern(ReadPattern(in));

    Transformer* t = ReadTransformer(in);
    rect->SetTransformer(t);
    Unref(t);

    SetGraphic(rect);
}
