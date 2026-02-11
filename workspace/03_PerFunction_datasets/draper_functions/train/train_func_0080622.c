kmo_create_armNameStruct2(objSkyStruct *obj_sky_struct,
                                        cpl_frameset *frameset,
                                        const char *frameType,
                                        const cpl_vector *ifus,
                                        const char *name,
                                        cpl_array **unused_ifus,
                                        const int *bounds,
                                        const char *mapping_mode,
                                        int acceptAllSky)
{
    armNameStruct       *arm_name_struct    = NULL;

    KMO_TRY
    {
        KMO_TRY_ASSURE((obj_sky_struct != NULL) &&
                       (frameset != NULL) &&
                       (unused_ifus != NULL) &&
                       (bounds != NULL),
                       CPL_ERROR_ILLEGAL_INPUT,
                       "Not all inputs are provided!");

        KMO_TRY_EXIT_IF_NULL(
            arm_name_struct = cpl_calloc(1, sizeof(armNameStruct)));

        KMO_TRY_EXIT_IF_NULL(
            arm_name_struct->obj_sky_struct = obj_sky_struct);

        KMO_TRY_EXIT_IF_ERROR(
            kmo_priv_create_armNameStruct(arm_name_struct,
                                          frameset,
                                          frameType,
                                          ifus,
                                          name,
                                          unused_ifus,
                                          bounds,
                                          mapping_mode,
                                          acceptAllSky));
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();
        kmo_delete_armNameStruct(arm_name_struct);
    }

    return arm_name_struct;
}
