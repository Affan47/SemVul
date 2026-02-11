transform(float m11, float m12, float m21, float m22, float dx, float dy)
{
    dirty |= DrtTransform;

    bool& infinityTransform = activeState().infinityTransform;
    infinityTransform |= isInfArg(m11) | isInfArg(m12) | isInfArg(m21) | isInfArg(m22) |
                         isInfArg(dx)  | isInfArg(dy);
    if (infinityTransform) return;

    activeState().transform *= QTransform(m11, m12, 0.0f, m21, m22, 0.0f, dx, dy, 1.0f);
}
