Transformation(ostream& out, const char* keyword, Graphic* gr) {
    Transformer* t = gr ? gr->GetTransformer() : GetOverlayComp()->GetGraphic()->GetTransformer();
    Transformer identity;

    if (t != nil && *t != identity) {
	char key[strlen(keyword)+4];
	sprintf(key," :%s ",keyword);
	float a00, a01, a10, a11, a20, a21;
	t->GetEntries(a00, a01, a10, a11, a20, a21);
	out << key;
	out << a00 << "," << a01 << "," << a10 << ",";
	out << a11 << "," << a20 << "," << a21;
    }
}
