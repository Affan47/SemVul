activate_run_state(struct fpi_ssm *ssm)
{
	struct fp_img_dev *dev = ssm->priv;


	switch (ssm->cur_state) {
	case WRITE_INIT:
		fp_dbg("write init");
		aes_write_regv(dev, init, G_N_ELEMENTS(init), generic_write_regv_cb, ssm);
		break;
	}
}
