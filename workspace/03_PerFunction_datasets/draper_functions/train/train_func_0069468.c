Read (istream& in) {
    GraphicComp::Read(in);
    Graphic* g = GetGraphic();

    int count;
    in >> count;

    for (int i = 0; i < count; ++i) {
      GraphicComp* gc = (GraphicComp*)unidraw->GetCatalog()->ReadComponent(in);
      if(gc != nil)
        Append(gc);
    }

    g->FillBg(ReadBgFilled(in));
    g->SetBrush(ReadBrush(in));
    PSColor* fg = ReadColor(in);
    PSColor* bg = ReadColor(in);
    g->SetColors(fg, bg);
    g->SetFont(ReadFont(in));
    g->SetPattern(ReadPattern(in));

    Transformer* t = ReadTransformer(in);
    g->SetTransformer(t);
    Unref(t);
}
