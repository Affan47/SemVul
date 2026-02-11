kmo_dfs_load_vector(cpl_frameset *frameset,
                                const char *category,
                                int device,
                                int noise)
{
    cpl_frame       *frame = NULL;
    kmclipm_vector  *vec   = NULL;
    int             index  = 0;

    KMO_TRY
    {
        KMO_TRY_ASSURE(frameset != NULL,
                       CPL_ERROR_NULL_INPUT,
                       "Not all input data provided!");

        KMO_TRY_ASSURE(device >= 0,
                       CPL_ERROR_ILLEGAL_INPUT,
                       "device number is negative!");

        KMO_TRY_ASSURE((noise == 0) || (noise == 1),
                       CPL_ERROR_ILLEGAL_INPUT,
                       "noise must be 0 or 1!");

        frame = kmo_dfs_get_frame(frameset, category);
        KMO_TRY_CHECK_ERROR_STATE();

        if (frame != NULL) {
            index = kmo_identify_index(cpl_frame_get_filename(frame), device,
                                       noise);
            KMO_TRY_CHECK_ERROR_STATE();

            KMO_TRY_EXIT_IF_NULL(
                vec = kmclipm_vector_load(cpl_frame_get_filename(frame), index));
        }
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();

        kmclipm_vector_delete(vec); vec = NULL;
    }

    return vec;
}
