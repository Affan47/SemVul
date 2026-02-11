Definition (ostream& out) {
    TextOvComp* comp = (TextOvComp*) GetSubject();
    TextGraphic* g = comp->GetText();
    const char* text = g->GetOriginal();

    int h = g->GetLineHeight();
    out << "text(";
    out << h << ",";
    int indent_level = 0;
    Component* parent = comp;
    do {
	parent = parent->GetParent();
	indent_level++;
    } while (parent != nil);
    ParamList::output_text(out, text, indent_level);

    float sep = g->GetLineHeight() - 1;
    Transformer corrected, *t = g->GetTransformer();
    corrected.Translate(0., sep);
    if (t == nil) {
        g->SetTransformer(&corrected);
        TextGS(out);
        g->SetTransformer(t);

    } else {
        t->Reference();
        corrected.Postmultiply(t);
        g->SetTransformer(&corrected);
        TextGS(out);
        g->SetTransformer(t);
        Unref(t);
    }
    Annotation(out);
    Attributes(out);
    out << ")";

    return out.good();
}
