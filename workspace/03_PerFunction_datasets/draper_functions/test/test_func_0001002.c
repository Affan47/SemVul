add_invalidated_bounds(InvalidatedRanges& ranges, bool force)
{
    if (!force && !invalidated()) return;

    ranges.add(m_old_invalidated_ranges);

    SWFRect bounds;
    bounds.expand_to_transformed_rect(getWorldMatrix(*this), getBounds());
    ranges.add(bounds.getRange());

}
