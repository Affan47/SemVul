vp3054_i2c_remove(struct cx8802_dev *dev)
{
	struct vp3054_i2c_state *vp3054_i2c = dev->vp3054;

	if (vp3054_i2c == NULL ||
	    dev->core->boardnr != CX88_BOARD_DNTV_LIVE_DVB_T_PRO)
		return;

	i2c_del_adapter(&vp3054_i2c->adap);
	kfree(vp3054_i2c);
}
