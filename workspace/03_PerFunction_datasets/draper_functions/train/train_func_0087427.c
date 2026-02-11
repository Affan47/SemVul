update_bbox(int type, VPoint vp)
{
    BBox_type *bbp;

    switch(type) {
    case BBOX_TYPE_GLOB:

        if (get_draw_mode() == FALSE) {
            return;
        }
        bbp = &bboxes[0];
        break;
    case BBOX_TYPE_TEMP:
        bbp = &bboxes[1];
        break;
    default:
        errmsg ("Incorrect call of update_bbox()");
        return;
    }
    if (bbp->active == TRUE) {
        if (is_vpoint_inside(bbp->v, vp, 0.0) == FALSE) {
            if (is_valid_bbox(bbp->v)) {
                bbp->v.xv1 = MIN2(bbp->v.xv1, vp.x);
                bbp->v.xv2 = MAX2(bbp->v.xv2, vp.x);
                bbp->v.yv1 = MIN2(bbp->v.yv1, vp.y);
                bbp->v.yv2 = MAX2(bbp->v.yv2, vp.y);
            } else {
                bbp->v.xv1 = vp.x;
                bbp->v.xv2 = vp.x;
                bbp->v.yv1 = vp.y;
                bbp->v.yv2 = vp.y;
            }
        }
    }
}
