Adjust(HSBColor& dest, HSBColor& destTarget,
                 const HSBColor& adj, const HSBColor& adjTarg, int assign)
{
    int current = assign & HueMask; bool twoValue = current == Hue2Value;
    dest.h = adjustHue(dest.h, adj.h, current, twoValue ? adjTarg.h : destTarget.h);
    if (!twoValue) destTarget.h = adjustHue(destTarget.h, adjTarg.h);

    current = assign & SaturationMask;   twoValue = current == Saturation2Value;
    dest.s =    adjust(dest.s, adj.s, current, twoValue ? adjTarg.s : destTarget.s);
    if (!twoValue) destTarget.s =    adjust(destTarget.s, adjTarg.s);

    current = assign & BrightnessMask;   twoValue = current == Brightness2Value;
    dest.b =    adjust(dest.b, adj.b, current, twoValue ? adjTarg.b : destTarget.b);
    if (!twoValue) destTarget.b =    adjust(destTarget.b, adjTarg.b);

    current = assign & AlphaMask;        twoValue = current == Alpha2Value;
    dest.a =    adjust(dest.a, adj.a, current, twoValue ? adjTarg.a : destTarget.a);
    if (!twoValue) destTarget.a =    adjust(destTarget.a, adjTarg.a);
}
