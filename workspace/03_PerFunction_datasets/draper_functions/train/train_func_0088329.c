dvb_bt8xx_remove(struct bttv_sub_device *sub)
{
	struct dvb_bt8xx_card *card = dev_get_drvdata(&sub->dev);

	dprintk("dvb_bt8xx: unloading card%d\n", card->bttv_nr);

	bt878_stop(card->bt);
	tasklet_kill(&card->bt->tasklet);
	dvb_net_release(&card->dvbnet);
	card->demux.dmx.remove_frontend(&card->demux.dmx, &card->fe_mem);
	card->demux.dmx.remove_frontend(&card->demux.dmx, &card->fe_hw);
	dvb_dmxdev_release(&card->dmxdev);
	dvb_dmx_release(&card->demux);
	if (card->fe) {
		dvb_unregister_frontend(card->fe);
		dvb_frontend_detach(card->fe);
	}
	dvb_unregister_adapter(&card->dvb_adapter);

	kfree(card);
}
