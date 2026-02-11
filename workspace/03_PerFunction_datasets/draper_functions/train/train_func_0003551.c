gv_scroll_lines(GVDataPresentation *dp, offset_type current_offset, int delta)
{
    g_return_val_if_fail (dp!=NULL, 0);
    g_return_val_if_fail (dp->scroll_lines!=NULL, 0);
    return dp->scroll_lines(dp, current_offset, delta);
}
