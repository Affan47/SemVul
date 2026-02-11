ibvs_mirror_write(
  IN ibvs_t* const p_ibvs,
  IN uint16_t lid,
  IN uint32_t rx_mirror,
  IN uint32_t tx_mirror)
{
  osm_mad_addr_t        mad_addr;
  osm_madw_t            *p_madw;
  ib_api_status_t status;
  osm_madw_t     *p_madw_arr[1];
  ib_vs_t        res_mad;

  OSM_LOG_ENTER(&(IbisObj.log));

  osm_log(&(IbisObj.log), OSM_LOG_DEBUG,
          "ibvs_mirror_write: "
          " Sending VS mirror set to lid:0x%04X",
		  lid);

  __ibvs_init_mad_addr(lid, &mad_addr);

  p_madw =
    osm_mad_pool_get(&(IbisObj.mad_pool),
                     p_ibvs->h_bind, MAD_PAYLOAD_SIZE, &mad_addr);

  *p_madw_arr = p_madw;

  __ibvs_init_mad_hdr(VENDOR_SET, VS_MIRROR, SWITCH_PORT, p_madw);
 ((ib_vs_t *)p_madw->p_mad)->vendor_key =
 cl_hton64(IbisObj.p_opt->v_key);

  ((ib_vs_t *)p_madw->p_mad)->data[0] = cl_hton32(rx_mirror);
 ((ib_vs_t *)p_madw->p_mad)->data[1] = cl_hton32(tx_mirror);


  status = ibis_gsi_send_sync_mad_batch(
    &(IbisObj.mad_ctrl),
    p_ibvs->h_bind,
    1,
    p_madw_arr,
    sizeof(ib_vs_t),
    (uint8_t*)&res_mad);

  if (status == IB_SUCCESS)
    status = ibis_get_mad_status((ib_mad_t*)&res_mad);

  OSM_LOG_EXIT(&(IbisObj.log));
  return (status);
}
