gnome_rr_rotation_from_xrotation (Rotation r)
{
    int i;
    GnomeRRRotation result = 0;

    for (i = 0; i < G_N_ELEMENTS (rotation_map); ++i)
    {
	if (r & rotation_map[i].xrot)
	    result |= rotation_map[i].rot;
    }

    return result;
}
