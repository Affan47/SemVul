Definition (ostream& out) {
    ArrowOpenBSpline* aml = (ArrowOpenBSpline*) GetGraphicComp()->GetGraphic();

    const Coord* x, *y;
    int n = aml->GetOriginal(x, y);
    float arrow_scale = aml->ArrowScale();

    out << "Begin " << MARK << " " << Name() << "\n";
    MinGS(out);
    out << MARK << " " << n << "\n";
    for (int i = 0; i < n; i++) {
        out << x[i] << " " << y[i] << "\n";
    }
    out << n << " " << Name() << "\n";
    out << MARK << " " << arrow_scale << "\n";
    out << "End\n\n";

    return out.good();
}
