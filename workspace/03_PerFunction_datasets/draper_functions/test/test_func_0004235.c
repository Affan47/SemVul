r6_surface_init_2d(struct radeon_surface_manager *surf_man,
                              struct radeon_surface *surf,
                              uint64_t offset, unsigned start_level)
{
    uint32_t xalign, yalign, zalign, tilew;
    unsigned i;


    tilew = 8;
    zalign = 1;
    xalign = (surf_man->hw_info.group_bytes * surf_man->hw_info.num_banks) /
             (tilew * surf->bpe * surf->nsamples);
    xalign = MAX2(tilew * surf_man->hw_info.num_banks, xalign);
    yalign = tilew * surf_man->hw_info.num_pipes;
    if (surf->flags & RADEON_SURF_SCANOUT) {
        xalign = MAX2((surf->bpe == 1) ? 64 : 32, xalign);
    }
    if (!start_level) {
        surf->bo_alignment =
            MAX2(surf_man->hw_info.num_pipes *
                 surf_man->hw_info.num_banks *
                 surf->nsamples * surf->bpe * 64,
                 xalign * yalign * surf->nsamples * surf->bpe);
    }


    for (i = start_level; i <= surf->last_level; i++) {
        surf->level[i].mode = RADEON_SURF_MODE_2D;
        surf_minify(surf, surf->level+i, surf->bpe, i, xalign, yalign, zalign, offset);
        if (surf->level[i].mode == RADEON_SURF_MODE_1D) {
            return r6_surface_init_1d(surf_man, surf, offset, i);
        }

        offset = surf->bo_size;
        if (i == 0) {
            offset = ALIGN(offset, surf->bo_alignment);
        }
    }
    return 0;
}
