giblorb_initialize_map(giblorb_map_t *map)
{


    int ix, jx;
    giblorb_result_t chunkres;
    giblorb_err_t err;
    char *ptr;
    glui32 len;
    glui32 numres;
    int gotindex = FALSE;

    for (ix=0; ix<map->numchunks; ix++) {
        giblorb_chunkdesc_t *chu = &map->chunks[ix];

        switch (chu->type) {

            case giblorb_ID_RIdx:


                if (gotindex)
                    return giblorb_err_Format;
                err = giblorb_load_chunk_by_number(map, giblorb_method_Memory,
                    &chunkres, ix);
                if (err)
                    return err;

                ptr = chunkres.data.ptr;
                len = chunkres.length;
                numres = giblorb_native4(ptr+0);

                if (numres) {
                    int ix2;
                    giblorb_resdesc_t *resources;
                    giblorb_resdesc_t **ressorted;

                    if (len != numres*12+4)
                        return giblorb_err_Format;

                    resources = (giblorb_resdesc_t *)giblorb_malloc(numres
                        * sizeof(giblorb_resdesc_t));
                    ressorted = (giblorb_resdesc_t **)giblorb_malloc(numres
                        * sizeof(giblorb_resdesc_t *));
                    if (!ressorted || !resources)
                        return giblorb_err_Alloc;

                    ix2 = 0;
                    for (jx=0; jx<numres; jx++) {
                        giblorb_resdesc_t *res = &(resources[jx]);
                        glui32 respos;

                        res->usage = giblorb_native4(ptr+jx*12+4);
                        res->resnum = giblorb_native4(ptr+jx*12+8);
                        respos = giblorb_native4(ptr+jx*12+12);

                        while (ix2 < map->numchunks
                            && map->chunks[ix2].startpos < respos)
                            ix2++;

                        if (ix2 >= map->numchunks
                            || map->chunks[ix2].startpos != respos)
                            return giblorb_err_Format;


                        res->chunknum = ix2;

                        ressorted[jx] = res;
                    }


                    giblorb_qsort(ressorted, numres);

                    map->numresources = numres;
                    map->resources = resources;
                    map->ressorted = ressorted;
                }

                giblorb_unload_chunk(map, ix);
                gotindex = TRUE;
                break;

        }
    }

    return giblorb_err_None;
}
