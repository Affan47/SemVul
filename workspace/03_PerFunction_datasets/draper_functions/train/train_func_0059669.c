add_invalidated_bounds(InvalidatedRanges& ranges, bool force)
{
    ranges.add(m_old_invalidated_ranges);
    if (visible() && (_invalidated||force))
    {
        SWFRect bounds;
        bounds.expand_to_transformed_rect(getWorldMatrix(*this), getBounds());
        ranges.add(bounds.getRange());
    }
}
