operator==(const R2Span& span) const
{

    if (Start() != span.Start()) return FALSE;
    if (End() != span.End()) return FALSE;
    return TRUE;
}
