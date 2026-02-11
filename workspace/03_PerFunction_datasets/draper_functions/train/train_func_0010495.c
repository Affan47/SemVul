xbaeComputeSize(XbaeMatrixWidget mw, Boolean compute_width,
                Boolean compute_height)
#else
xbaeComputeSize(mw, compute_width, compute_height)
XbaeMatrixWidget mw;
Boolean compute_width;
Boolean compute_height;
#endif
{
    unsigned long full_width = NON_FIXED_TOTAL_WIDTH(mw) +
        FIXED_COLUMN_WIDTH(mw) + TRAILING_FIXED_COLUMN_WIDTH(mw) +
        ROW_LABEL_WIDTH(mw) + 2 * mw->manager.shadow_thickness;
    unsigned long full_height = CELL_TOTAL_HEIGHT(mw) +
        FIXED_ROW_HEIGHT(mw) + TRAILING_FIXED_ROW_HEIGHT(mw) +
        COLUMN_LABEL_HEIGHT(mw) + 2 * mw->manager.shadow_thickness;
    unsigned long width, height;


    if (mw->matrix.visible_columns)
        width = ROW_LABEL_WIDTH(mw) + 2 * mw->manager.shadow_thickness +
            COLUMN_WIDTH(mw, (mw->matrix.visible_columns +
                              mw->matrix.fixed_columns) - 1) +
            COLUMN_POSITION(mw, mw->matrix.fixed_columns +
                            mw->matrix.visible_columns - 1) +
            TRAILING_FIXED_COLUMN_WIDTH(mw);
    else if (compute_width)
        width = full_width;
    else
        width = mw->core.width;


    if (mw->matrix.visible_rows)
        height = mw->matrix.visible_rows * ROW_HEIGHT(mw) +
            TRAILING_FIXED_ROW_HEIGHT(mw) + FIXED_ROW_HEIGHT(mw) +
            COLUMN_LABEL_HEIGHT(mw) + 2 * mw->manager.shadow_thickness;
    else if (compute_height)
        height = full_height;
    else
        height = mw->core.height;


    mw->core.width = width;
    mw->core.height = height;


    if (((width < full_width) ||
         (XmDISPLAY_STATIC == mw->matrix.hsb_display_policy)) &&
        (compute_height || mw->matrix.visible_rows) &&
        (XmDISPLAY_NONE != mw->matrix.hsb_display_policy))
        mw->core.height += HORIZ_SB_HEIGHT(mw);


    if (((height < full_height) ||
         (XmDISPLAY_STATIC == mw->matrix.vsb_display_policy)) &&
        (compute_width || mw->matrix.visible_columns) &&
        (XmDISPLAY_NONE != mw->matrix.vsb_display_policy))
        mw->core.width += VERT_SB_WIDTH(mw);


    mw->matrix.desired_width = mw->core.width;
    mw->matrix.desired_height = mw->core.height;
}
