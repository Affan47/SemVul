ff_load_extents_file(FILE * f, fr_vector<ft_uoff> & ret_list, ft_uoff & ret_block_size_bitmask)
{
    {
        char header[200];
        for (ft_size i = 0; i < 6; i++) {
            if (fgets(header, sizeof(header), f) == NULL || header[0] != '#')
                return EPROTO;
        }
    }

    ft_ull physical, logical, length = 0, user_data;
    if (fscanf(f, "count %"FT_ULL"\n", & length) != 1)
        return EPROTO;

    if (fscanf(f, "physical\tlogical\tlength\tuser_data\n") < 0)
        return EPROTO;

    ft_uoff block_size_bitmask = ret_block_size_bitmask;
    ft_size i = ret_list.size(), n = (ft_size) length;

    ret_list.resize(n += i);
    for (; i < n; i++) {
        if (fscanf(f, "%"FT_ULL" %"FT_ULL" %"FT_ULL" %"FT_ULL"\n", &physical, &logical, &length, &user_data) != 4)
            return EPROTO;

        fr_extent<ft_uoff> & extent = ret_list[i];

        block_size_bitmask |=
            (extent.physical() = (ft_uoff) physical) |
            (extent.logical()  = (ft_uoff) logical) |
            (extent.length()   = (ft_uoff) length);

        extent.user_data() = (ft_size) user_data;
    }
    ret_block_size_bitmask = block_size_bitmask;
    return 0;
}
