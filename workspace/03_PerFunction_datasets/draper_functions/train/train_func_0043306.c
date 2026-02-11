lasso_button_press(gpaint_tool * tool, int x, int y)
{
    gpaint_lasso *lasso = GPAINT_LASSO(tool);
    debug_fn();
    if (drawing_in_bounds(tool->drawing, x, y))
    {
        selection_remove_points(lasso->selection);
        selection_add_point(lasso->selection, x, y);
    }
}
