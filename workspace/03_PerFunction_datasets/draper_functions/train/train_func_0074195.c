hud_lock_secondary_weapon_changed(ship_weapon *swp)
{

	if ( swp->current_secondary_bank != Player_ai->last_secondary_index ) {
		return 1;
	}

	return 0;


}
