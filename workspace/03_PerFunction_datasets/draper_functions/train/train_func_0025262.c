rsvg_radial_gradient_fix_fallback (RsvgRadialGradient * grad)
{
    RsvgNode *ufallback;
    ufallback = grad->fallback;
    while (ufallback != NULL) {
        if (RSVG_NODE_TYPE (ufallback) == RSVG_NODE_TYPE_RADIAL_GRADIENT) {
            RsvgRadialGradient *fallback = (RsvgRadialGradient *) ufallback;
            if (!grad->hascx && fallback->hascx) {
                grad->hascx = TRUE;
                grad->cx = fallback->cx;
            }
            if (!grad->hascy && fallback->hascy) {
                grad->hascy = TRUE;
                grad->cy = fallback->cy;
            }
            if (!grad->hasfx && fallback->hasfx) {
                grad->hasfx = TRUE;
                grad->fx = fallback->fx;
            }
            if (!grad->hasfy && fallback->hasfy) {
                grad->hasfy = TRUE;
                grad->fy = fallback->fy;
            }
            if (!grad->hasr && fallback->hasr) {
                grad->hasr = TRUE;
                grad->r = fallback->r;
            }
            if (!grad->hastransform && fallback->hastransform) {
                grad->hastransform = TRUE;
                grad->affine = fallback->affine;
            }
            if (!grad->hasspread && fallback->hasspread) {
                grad->hasspread = TRUE;
                grad->spread = fallback->spread;
            }
            if (!grad->hasbbox && fallback->hasbbox) {
                grad->hasbbox = TRUE;
                grad->obj_bbox = fallback->obj_bbox;
            }
            if (!hasstop (grad->super.children) && hasstop (fallback->super.children)) {
                grad->super.children = fallback->super.children;
            }
            ufallback = fallback->fallback;
        } else if (RSVG_NODE_TYPE (ufallback) == RSVG_NODE_TYPE_LINEAR_GRADIENT) {
            RsvgLinearGradient *fallback = (RsvgLinearGradient *) ufallback;
            if (!grad->hastransform && fallback->hastransform) {
                grad->hastransform = TRUE;
                grad->affine = fallback->affine;
            }
            if (!grad->hasspread && fallback->hasspread) {
                grad->hasspread = TRUE;
                grad->spread = fallback->spread;
            }
            if (!grad->hasbbox && fallback->hasbbox) {
                grad->hasbbox = TRUE;
                grad->obj_bbox = fallback->obj_bbox;
            }
            if (!hasstop (grad->super.children) && hasstop (fallback->super.children)) {
                grad->super.children = fallback->super.children;
            }
            ufallback = fallback->fallback;
        }
    }
}
