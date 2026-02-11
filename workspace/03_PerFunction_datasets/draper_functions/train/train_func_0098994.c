buildin_repairitem(struct script_state *st)
{
	struct map_session_data *sd=script_rid2sd(st);

	if(sd) {
		int i, c = 0;

		for(i=0;i<MAX_INVENTORY;i++) {
			if(sd->status.inventory[i].nameid > 0 && sd->status.inventory[i].amount > 0 && sd->status.inventory[i].attribute){
				sd->status.inventory[i].attribute = 0;
				c++;
			}
		}
		if(c > 0) {
			clif_itemlist(sd);
			clif_equiplist(sd);
		}
	}
	return 0;
}
