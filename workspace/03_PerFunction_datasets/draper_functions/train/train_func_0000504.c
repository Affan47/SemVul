hdrl_set_masks_on_imagelist(cpl_imagelist * list, cpl_mask ** masks)
{
    cpl_ensure_code(list, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(masks, CPL_ERROR_NULL_INPUT);

    for (size_t i = 0; i < (size_t)cpl_imagelist_get_size(list); i++) {
        cpl_image * img = cpl_imagelist_get(list, i);
        cpl_mask * img_mask = cpl_image_get_bpm(img);

        cpl_mask_xor(img_mask, img_mask);

        cpl_mask_or(img_mask, masks[i]);
    }

    return cpl_error_get_code();
}
