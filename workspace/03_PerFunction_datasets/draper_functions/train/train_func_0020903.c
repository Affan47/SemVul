GC_add_map_entry(size_t granules)
  {
    unsigned displ;
    short * new_map;

    if (granules > BYTES_TO_GRANULES(MAXOBJBYTES)) granules = 0;
    if (GC_obj_map[granules] != 0) {
        return(TRUE);
    }
    new_map = (short *)GC_scratch_alloc(MAP_LEN * sizeof(short));
    if (new_map == 0) return(FALSE);
    GC_COND_LOG_PRINTF(
                "Adding block map for size of %u granules (%u bytes)\n",
                (unsigned)granules, (unsigned)GRANULES_TO_BYTES(granules));
    if (granules == 0) {
      for (displ = 0; displ < BYTES_TO_GRANULES(HBLKSIZE); displ++) {
        new_map[displ] = 1;
      }
    } else {
      for (displ = 0; displ < BYTES_TO_GRANULES(HBLKSIZE); displ++) {
        new_map[displ] = (short)(displ % granules);
      }
    }
    GC_obj_map[granules] = new_map;
    return(TRUE);
  }
