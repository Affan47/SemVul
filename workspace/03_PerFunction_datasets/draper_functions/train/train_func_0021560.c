add_invalidated_bounds(InvalidatedRanges& ranges, bool force)
{

    if (!visible() || invisible(getCxForm(*this))) {
        ranges.add(m_old_invalidated_ranges);
        return;
    }

    if (!invalidated() && !childInvalidated() && !force) return;


    if (invalidated() || force) {

        ranges.add(m_old_invalidated_ranges);
    }

    _displayList.add_invalidated_bounds(ranges, force || invalidated());


    SWFRect bounds;
    bounds.expand_to_transformed_rect(getWorldMatrix(*this),
            _drawable.getBounds());

    ranges.add(bounds.getRange());
}
