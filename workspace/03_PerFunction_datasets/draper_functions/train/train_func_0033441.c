gs_delete_surf(int id)
{
    geosurf *fs;

    G_debug(5, "gs_delete_surf");

    fs = gs_get_surf(id);

    if (fs) {
	gs_free_surf(fs);
    }

    return;
}
