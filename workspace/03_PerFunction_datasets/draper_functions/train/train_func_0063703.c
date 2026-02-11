InterpretManipulator (Manipulator* m) {
    DragManip* dm = (DragManip*) m;
    Editor* ed = dm->GetViewer()->GetEditor();
    Tool* tool = dm->GetTool();
    Transformer* rel = dm->GetTransformer();
    Command* cmd = nil;

    if (tool->IsA(GRAPHIC_COMP_TOOL)) {
        GrowingVertices* gv = (GrowingVertices*) dm->GetRubberband();
        Coord* x, *y;
        int n, pt;
        gv->GetCurrent(x, y, n, pt);

        if (n > 2 || x[0] != x[1] || y[0] != y[1]) {
            BrushVar* brVar = (BrushVar*) ed->GetState("BrushVar");
            PatternVar* patVar = (PatternVar*) ed->GetState("PatternVar");
            ColorVar* colVar = (ColorVar*) ed->GetState("ColorVar");

            if (rel != nil) {
                rel = new Transformer(rel);
                rel->Invert();
            }

            Graphic* pg = GetGraphicComp()->GetGraphic();
            SF_MultiLine* polygon = new SF_MultiLine(x, y, n, pg);

            if (brVar != nil) polygon->SetBrush(brVar->GetBrush());
            if (patVar != nil) polygon->SetPattern(patVar->GetPattern());

            if (colVar != nil) {
	        polygon->FillBg(!colVar->GetBgColor()->None());
                polygon->SetColors(colVar->GetFgColor(), colVar->GetBgColor());
            }
            polygon->SetTransformer(rel);
            Unref(rel);
            cmd = new PasteCmd(ed, new Clipboard(new MultiLineComp(polygon)));
        }
        delete x;
        delete y;

    } else if (tool->IsA(RESHAPE_TOOL)) {
        GrowingVertices* gv = (GrowingVertices*) dm->GetRubberband();
        Coord* x, *y;
        int n, pt;
        gv->RemoveVertex();
        gv->GetCurrent(x, y, n, pt);

	if (rel != nil) {
            rel = new Transformer(rel);
            rel->Invert();
        }

        SF_MultiLine* polygon = new SF_MultiLine(x, y, n, GetGraphic());
	delete x;
	delete y;
        polygon->SetTransformer(rel);
        Unref(rel);
	cmd = new ReplaceCmd(ed, new MultiLineComp(polygon));

    } else {
        cmd = VerticesView::InterpretManipulator(m);
    }
    return cmd;
}
