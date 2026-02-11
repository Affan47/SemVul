R3Contains(const R3Span& span, const R3Box& box)
{

    if (!R3Contains(span.Line(), box)) return FALSE;
    if (!R3Contains(span, box.Min())) return FALSE;
    if (!R3Contains(span, box.Max())) return FALSE;
    return TRUE;
}
