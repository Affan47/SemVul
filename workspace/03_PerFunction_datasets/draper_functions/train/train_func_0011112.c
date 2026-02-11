get_remaining_axes (Axis axis) {
    if (!is_single_axis_direction (axis)) return std::make_pair (NONE, NONE);
    Axis plane = orth_plane_or_axis (axis);
    return std::make_pair (extract_first_axis_direction (plane), extract_second_axis_direction (plane));
}

}
