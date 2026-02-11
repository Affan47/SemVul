hawki_rebuild_detectors(
        const cpl_image *   ima1,
        const cpl_image *   ima2,
        const cpl_image *   ima3,
        const cpl_image *   ima4)
{
    cpl_image           *   ima ;


    if (ima1 == NULL) return NULL ;
    if (ima2 == NULL) return NULL ;
    if (ima3 == NULL) return NULL ;
    if (ima4 == NULL) return NULL ;
    if (cpl_image_get_type(ima1)!=cpl_image_get_type(ima2)) return NULL ;
    if (cpl_image_get_type(ima1)!=cpl_image_get_type(ima3)) return NULL ;
    if (cpl_image_get_type(ima1)!=cpl_image_get_type(ima4)) return NULL ;


    ima = cpl_image_new(4096, 4096, cpl_image_get_type(ima1)) ;


    if (cpl_image_copy(ima, ima1, 1, 1) != CPL_ERROR_NONE) {
        cpl_image_delete(ima) ;
        return NULL ;
    }
    if (cpl_image_copy(ima, ima2, 2049, 1) != CPL_ERROR_NONE) {
        cpl_image_delete(ima) ;
        return NULL ;
    }
    if (cpl_image_copy(ima, ima3, 2049, 2049) != CPL_ERROR_NONE) {
        cpl_image_delete(ima) ;
        return NULL ;
    }
    if (cpl_image_copy(ima, ima4, 1, 2049) != CPL_ERROR_NONE) {
        cpl_image_delete(ima) ;
        return NULL ;
    }
    return ima ;
}
