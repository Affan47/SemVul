bfad_iocmd_lunmask_reset_lunscan_mode(struct bfad_s *bfad, int lunmask_cfg)
{
	struct bfad_im_port_s *pport_im = bfad->pport.im_port;
	struct bfad_vport_s *vport = NULL;


	bfad_reset_sdev_bflags(pport_im, lunmask_cfg);


	list_for_each_entry(vport, &bfad->vport_list, list_entry)
		bfad_reset_sdev_bflags(vport->drv_port.im_port, lunmask_cfg);
}
