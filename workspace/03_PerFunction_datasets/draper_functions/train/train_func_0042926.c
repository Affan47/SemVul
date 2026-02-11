gx_ht_init_cache(const gs_memory_t *mem, gx_ht_cache * pcache, const gx_ht_order * porder)
{
    uint width = porder->width;
    uint height = porder->height;
    uint size = width * height + 1;
    int width_unit =
    (width <= ht_mask_bits / 2 ? ht_mask_bits / width * width :
     width);
    int height_unit = height;
    uint raster = porder->raster;
    uint tile_bytes = raster * height;
    uint shift = porder->shift;
    int num_cached;
    int i;
    byte *tbits = pcache->bits;


    if (porder->num_bits >= size)
        size = porder->num_bits + 1;

    num_cached = pcache->bits_size / tile_bytes;
    if (num_cached > size)
        num_cached = size;
    if (num_cached > pcache->num_tiles)
        num_cached = pcache->num_tiles;
    if (num_cached == size &&
        tile_bytes * num_cached <= pcache->bits_size / 2
        ) {


        uint rep_raster =
        ((pcache->bits_size / num_cached) / height) &
        ~(align_bitmap_mod - 1);
        uint rep_count = rep_raster * 8 / width;


        if (rep_count > sizeof(ulong) * 8)
            rep_count = sizeof(ulong) * 8;
        width_unit = width * rep_count;
        raster = bitmap_raster(width_unit);
        tile_bytes = raster * height;
    }
    pcache->base_id = gs_next_ids(mem, porder->num_levels + 1);
    pcache->order = *porder;

    pcache->order.transfer = 0;
    pcache->num_cached = num_cached;
    pcache->levels_per_tile = (size + num_cached - 1) / num_cached;
    pcache->tiles_fit = -1;
    memset(tbits, 0, pcache->bits_size);
    for (i = 0; i < num_cached; i++, tbits += tile_bytes) {
        register gx_ht_tile *bt = &pcache->ht_tiles[i];

        bt->level = 0;
        bt->index = i;
        bt->tiles.data = tbits;
        bt->tiles.raster = raster;
        bt->tiles.size.x = width_unit;
        bt->tiles.size.y = height_unit;
        bt->tiles.rep_width = width;
        bt->tiles.rep_height = height;
        bt->tiles.shift = bt->tiles.rep_shift = shift;
        bt->tiles.num_planes = 1;
    }
    pcache->render_ht = gx_render_ht_default;
}
