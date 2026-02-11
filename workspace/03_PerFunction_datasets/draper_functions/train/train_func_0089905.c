dc1394_basler_sff_feature_print_all (dc1394camera_t* camera, FILE *fd)
{
    uint32_t i = DC1394_BASLER_SFF_FEATURE_MIN;
    while (i < DC1394_BASLER_SFF_FEATURE_MAX) {
        dc1394_basler_sff_feature_print (camera, i, fd);
        fprintf (fd, "\n");
        i++;
    }
    return DC1394_SUCCESS;
}
