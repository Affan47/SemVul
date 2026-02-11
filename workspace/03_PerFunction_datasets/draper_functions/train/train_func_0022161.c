il_sta_ucode_activate(struct il_priv *il, u8 sta_id)
{

	if (!(il->stations[sta_id].used & IL_STA_DRIVER_ACTIVE))
		IL_ERR("ACTIVATE a non DRIVER active station id %u addr %pM\n",
		       sta_id, il->stations[sta_id].sta.sta.addr);

	if (il->stations[sta_id].used & IL_STA_UCODE_ACTIVE) {
		D_ASSOC("STA id %u addr %pM already present"
			" in uCode (according to driver)\n", sta_id,
			il->stations[sta_id].sta.sta.addr);
	} else {
		il->stations[sta_id].used |= IL_STA_UCODE_ACTIVE;
		D_ASSOC("Added STA id %u addr %pM to uCode\n", sta_id,
			il->stations[sta_id].sta.sta.addr);
	}
}
