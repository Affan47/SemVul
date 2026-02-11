main (int argc, char **argv)
{
    dc1394camera_t *camera = NULL;
    uint64_t guid = 0x0LL;
    dc1394_t * d;
    dc1394camera_list_t * list;
    dc1394error_t err;

    d = dc1394_new ();
    if (!d)
        return 1;
    err=dc1394_camera_enumerate (d, &list);
    DC1394_ERR_RTN(err,"Failed to enumerate cameras");

    if (list->num == 0) {
        dc1394_log_error("No cameras found");
        return 1;
    }


    if (argc == 2) {
        if (!strcmp (argv[1], "--list-cameras"))
            list_cameras (d, list);
        else
            print_usage();
        dc1394_camera_free_list (list);
        dc1394_free (d);
        return 0;
    } else if (argc == 3) {
        if (!strcmp (argv[1], "--guid")) {
            if (sscanf (argv[2], "0x%"PRIx64, &guid) == 1) {
            } else {
                dc1394_camera_free_list (list);
                dc1394_free (d);
                return print_usage();
            }
        }
    } else if (argc != 1) {
        dc1394_camera_free_list (list);
        dc1394_free (d);
        return print_usage();
    }

    if (guid == 0x0LL) {
        printf ("I: found %d camera%s, working with camera 0\n", list->num,
                list->num == 1 ? "" : "s");
        camera = dc1394_camera_new (d, list->ids[0].guid);
    } else {
        camera = dc1394_camera_new (d, guid);
        if (camera == NULL) {
            dc1394_log_error("no camera with guid 0x%"PRIx64" found", guid);
            return 1;
        }

        printf ("I: found camera with guid 0x%"PRIx64"\n", guid);
    }

    dc1394_camera_print_info (camera, stdout);
    printf ("\nSFF feature info:\n");
    dc1394_basler_sff_feature_print_all (camera, stdout);
    dc1394_camera_free (camera);
    dc1394_camera_free_list (list);
    dc1394_free (d);
    return 0;
}
