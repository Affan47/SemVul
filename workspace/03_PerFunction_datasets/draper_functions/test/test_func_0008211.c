P_CheckAmmo (player_t* player)
{
    ammotype_t		ammo;
    int			count;

    ammo = weaponinfo[player->readyweapon].ammo;


    if (player->readyweapon == wp_bfg)
	count = deh_bfg_cells_per_shot;
    else if (player->readyweapon == wp_supershotgun)
	count = 2;
    else
	count = 1;


    if (ammo == am_noammo || player->ammo[ammo] >= count)
	return true;


    do
    {
	if (player->weaponowned[wp_plasma]
	    && player->ammo[am_cell]
	    && (gamemode != shareware) )
	{
	    player->pendingweapon = wp_plasma;
	}
	else if (player->weaponowned[wp_supershotgun]
		 && player->ammo[am_shell]>2
		 && (gamemode == commercial) )
	{
	    player->pendingweapon = wp_supershotgun;
	}
	else if (player->weaponowned[wp_chaingun]
		 && player->ammo[am_clip])
	{
	    player->pendingweapon = wp_chaingun;
	}
	else if (player->weaponowned[wp_shotgun]
		 && player->ammo[am_shell])
	{
	    player->pendingweapon = wp_shotgun;
	}
	else if (player->ammo[am_clip])
	{
	    player->pendingweapon = wp_pistol;
	}
	else if (player->weaponowned[wp_chainsaw])
	{
	    player->pendingweapon = wp_chainsaw;
	}
	else if (player->weaponowned[wp_missile]
		 && player->ammo[am_misl])
	{
	    player->pendingweapon = wp_missile;
	}
	else if (player->weaponowned[wp_bfg]
		 && player->ammo[am_cell]>40
		 && (gamemode != shareware) )
	{
	    player->pendingweapon = wp_bfg;
	}
	else
	{

	    player->pendingweapon = wp_fist;
	}

    } while (player->pendingweapon == wp_nochange);


    P_SetPsprite (player,
		  ps_weapon,
		  weaponinfo[player->readyweapon].downstate);

    return false;
}
