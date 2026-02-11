ifoRead_C_ADT_internal(ifo_handle_t *ifofile,
                                  c_adt_t *c_adt, unsigned int sector) {
  int i, info_length;

  if(!DVDFileSeek_(ifofile->file, sector * DVD_BLOCK_LEN))
    return 0;

  if(!(DVDReadBytes(ifofile->file, c_adt, C_ADT_SIZE)))
    return 0;

  B2N_16(c_adt->nr_of_vobs);
  B2N_32(c_adt->last_byte);

  info_length = c_adt->last_byte + 1 - C_ADT_SIZE;

  CHECK_ZERO(c_adt->zero_1);


  CHECK_VALUE(info_length % sizeof(cell_adr_t) == 0);


  if(info_length / sizeof(cell_adr_t) < c_adt->nr_of_vobs) {
    fprintf(stderr, "libdvdread: *C_ADT nr_of_vobs > available info entries\n");
    c_adt->nr_of_vobs = info_length / sizeof(cell_adr_t);
  }

  c_adt->cell_adr_table = (cell_adr_t *)malloc(info_length);
  if(!c_adt->cell_adr_table)
    return 0;

  if(info_length &&
     !(DVDReadBytes(ifofile->file, c_adt->cell_adr_table, info_length))) {
    free(c_adt->cell_adr_table);
    return 0;
  }

  for(i = 0; i < info_length/sizeof(cell_adr_t); i++) {
    B2N_16(c_adt->cell_adr_table[i].vob_id);
    B2N_32(c_adt->cell_adr_table[i].start_sector);
    B2N_32(c_adt->cell_adr_table[i].last_sector);

    CHECK_ZERO(c_adt->cell_adr_table[i].zero_1);
    CHECK_VALUE(c_adt->cell_adr_table[i].vob_id > 0);
    CHECK_VALUE(c_adt->cell_adr_table[i].vob_id <= c_adt->nr_of_vobs);
    CHECK_VALUE(c_adt->cell_adr_table[i].cell_id > 0);
    CHECK_VALUE(c_adt->cell_adr_table[i].start_sector <
                c_adt->cell_adr_table[i].last_sector);
  }

  return 1;
}
