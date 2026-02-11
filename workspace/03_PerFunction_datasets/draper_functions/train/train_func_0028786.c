aoecmd_cfg_cmd ( struct aoe_command *aoecmd,
			     void *data, size_t len ) {
	struct aoe_device *aoedev = aoecmd->aoedev;
	struct aoehdr *aoehdr = data;
	struct aoecfg *aoecfg = &aoehdr->payload[0].cfg;


	assert ( len == ( sizeof ( *aoehdr ) + sizeof ( *aoecfg ) ) );


	aoehdr->command = AOE_CMD_CONFIG;
	memset ( aoecfg, 0, sizeof ( *aoecfg ) );

	DBGC ( aoedev, "AoE %s/%08x CONFIG cmd\n",
	       aoedev_name ( aoedev ), aoecmd->tag );
}
