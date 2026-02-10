__ibvs_prep_flash_access_mad(
  IN ibvs_t* p_ibvs,
  IN uint16_t lid,
  IN uint8_t method,
  IN uint16_t attr_id,
  IN uint32_t attr_mod,
  IN uint8_t size,
  IN uint32_t data[],
  IN uint32_t address,
  OUT osm_madw_t **pp_madw)
{

  osm_mad_addr_t        mad_addr;
  osm_madw_t            *p_madw;
  uint8_t               i,dword_size;

  OSM_LOG_ENTER(&(IbisObj.log));

  osm_log(&(IbisObj.log), OSM_LOG_DEBUG,
          "__ibvs_prep_flash_access_mad: "
          " Sending VS Flash to lid:0x%04X method:0x:%X attr:0x%X mod:0x%X\n",
          lid, method, attr_id, attr_mod);

  dword_size = size / 4;

  __ibvs_init_mad_addr(lid, &mad_addr);

  p_madw = osm_mad_pool_get(
    &(IbisObj.mad_pool), p_ibvs->h_bind, MAD_PAYLOAD_SIZE, &mad_addr);

  *pp_madw = p_madw;

  __ibvs_init_mad_hdr(method, attr_id, attr_mod, p_madw);
  ((ib_vs_t *)p_madw->p_mad)->vendor_key = cl_hton64(IbisObj.p_opt->v_key);

  ((ib_vs_flash_t *)p_madw->p_mad)->size = cl_hton32(size);
  ((ib_vs_flash_t *)p_madw->p_mad)->offset = cl_hton32(address);

  if ((method == VENDOR_SET) || (attr_id == VS_FLASH_OPEN))
  {
    for (i=0;i<dword_size;i++) {
      ((ib_vs_flash_t *)p_madw->p_mad)->data[i] = cl_hton32(data[i]);
    };
  };

  OSM_LOG_EXIT(&(IbisObj.log));
}
