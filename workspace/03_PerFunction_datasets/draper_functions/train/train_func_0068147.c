UnscaledLength (float length, Transformer* t) {
    Transformer inverse(t);
    inverse.Invert();

    float x0 = 0, y0 = 0, x1 = length, y1 = 0;
    float tx0, ty0, tx1, ty1;

    inverse.Transform(x0, y0, tx0, ty0);
    inverse.Transform(x1, y1, tx1, ty1);

    return hypot(tx0 - tx1, ty0 - ty1);
}
