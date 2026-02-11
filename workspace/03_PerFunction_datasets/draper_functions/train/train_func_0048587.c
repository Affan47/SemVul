tdfxfb_delete_i2c_busses(struct tdfx_par *par)
{
	if (par->chan[0].par)
		i2c_del_adapter(&par->chan[0].adapter);
	par->chan[0].par = NULL;

	if (par->chan[1].par)
		i2c_del_adapter(&par->chan[1].adapter);
	par->chan[1].par = NULL;
}
