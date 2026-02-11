bfad_im_scsi_host_free(struct bfad_s *bfad, struct bfad_im_port_s *im_port)
{
	bfa_trc(bfad, bfad->inst_no);
	BFA_LOG(KERN_INFO, bfad, bfa_log_level, "Free scsi%d\n",
			im_port->shost->host_no);

	fc_remove_host(im_port->shost);

	scsi_remove_host(im_port->shost);
	scsi_host_put(im_port->shost);

	mutex_lock(&bfad_mutex);
	idr_remove(&bfad_im_port_index, im_port->idr_id);
	mutex_unlock(&bfad_mutex);
}
