jxr_set_QP_LOSSLESS(jxr_image_t image)
{
    unsigned char q[MAX_CHANNELS];
    int idx;
    for (idx = 0 ; idx < MAX_CHANNELS ; idx += 1)
        q[idx] = 0;

    jxr_set_QP_INDEPENDENT(image, q);

    if (image->num_channels == 1) {
        image->dc_component_mode = JXR_CM_UNIFORM;
        image->lp_component_mode = JXR_CM_UNIFORM;
        image->hp_component_mode = JXR_CM_UNIFORM;
    } else if (image->num_channels == 3) {
        image->dc_component_mode = JXR_CM_SEPARATE;
        image->lp_component_mode = JXR_CM_SEPARATE;
        image->hp_component_mode = JXR_CM_SEPARATE;
    }
}
