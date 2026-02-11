face_detector_lbp_detect(struct lbp *l, unsigned int *img, struct face *fa, int *maxfaces)
{
    int i;
#ifdef USE_OPENCL
    lbp_cl_detect(l->cl, img, l->detected_r);
#else
    int found;
    int width, height;
    width = l->width;
    height = l->height;

    #pragma omp parallel for private(found)
    for (i = 0; i < l->tasks.size(); i++) {
        found = lbp_detect(l, img, l->tasks[i].x, l->tasks[i].y, width, height, l->tasks[i].scale);
        if (found) {
            #pragma omp critical
            add_lbp_object(l, l->tasks[i].x, l->tasks[i].y, l->tasks[i].scale);
        }
    }

    face_detector_group_rectangle(l->detected_r, l->para.group_threshold, l->para.eps);
#endif


    if (l->detected_r.size() > (unsigned int)*maxfaces) {
        ALOGW("User provided maxface size not large enough");
    } else {
        *maxfaces = l->detected_r.size();
    }

    ALOGD("LBP tested: %ld", l->tasks.size());

    for (i = 0; i < *maxfaces; i++) {
        fa[i].x = l->detected_r[i].x;
        fa[i].y = l->detected_r[i].y;
        fa[i].width = l->detected_r[i].w;
        fa[i].height = l->detected_r[i].h;
        fa[i].confidence_level = 50;
    }
    l->detected_r.clear();

    return 0;
}
