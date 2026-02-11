release_resources(struct snd_dice *dice,
			      struct fw_iso_resources *resources)
{
	__be32 channel;


	channel = cpu_to_be32((u32)-1);
	if (resources == &dice->tx_resources)
		snd_dice_transaction_write_tx(dice, TX_ISOCHRONOUS,
					      &channel, sizeof(channel));
	else
		snd_dice_transaction_write_rx(dice, RX_ISOCHRONOUS,
					      &channel, sizeof(channel));

	fw_iso_resources_free(resources);
}
