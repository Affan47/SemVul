nouveau_abi16_fini(struct nouveau_abi16 *abi16)
{
	struct nouveau_cli *cli = (void *)abi16->device.object.client;
	struct nouveau_abi16_chan *chan, *temp;


	list_for_each_entry_safe(chan, temp, &abi16->channels, head) {
		nouveau_abi16_chan_fini(abi16, chan);
	}


	nvif_device_fini(&abi16->device);

	kfree(cli->abi16);
	cli->abi16 = NULL;
}
