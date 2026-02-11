gs_image_common_init(gs_image_enum * penum, gx_image_enum_common_t * pie,
            const gs_data_image_t * pim, gx_device * dev)
{


    int i;

    if (pim->Width == 0 || pim->Height == 0) {
        gx_image_end(pie, false);
        return 1;
    }
    image_enum_init(penum);
    penum->dev = dev;
    penum->info = pie;
    penum->num_planes = pie->num_planes;


    penum->height = pim->Height;
    for (i = 0; i < pie->num_planes; ++i) {
        penum->planes[i].pos = 0;
        penum->planes[i].source.size = 0;
        penum->planes[i].source.data = 0;
        penum->planes[i].row.data = 0;
        penum->planes[i].row.size = 0;
        penum->image_planes[i].data_x = 0;
    }

    penum->y = 0;
    penum->error = false;
    penum->wanted_varies = true;
    begin_planes(penum);
    return 0;
}
