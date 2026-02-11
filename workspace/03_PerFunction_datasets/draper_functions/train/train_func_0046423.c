sp_add( void )
{
  int j;
	for (j = 1; j < 100; j++)
	{
		if (pam.sprite[j].active == 0)
		{

			last_sprite_added = j;

			pam.sprite[j].active = 1;
            pam.sprite[j].frame = sp_frame;
            pam.sprite[j].seq = sp_seq;
			pam.sprite[j].x = spr[1].x;
			pam.sprite[j].y = spr[1].y;
			pam.sprite[j].size = spr[1].size;
			pam.sprite[j].type = sp_type;
			pam.sprite[j].brain = sp_brain;
			pam.sprite[j].speed = sp_speed;
			pam.sprite[j].base_walk = sp_base_walk;
			pam.sprite[j].base_idle = sp_base_idle;
			pam.sprite[j].base_attack = sp_base_attack;
			pam.sprite[j].base_hit = sp_base_hit;
			pam.sprite[j].timer = sp_timer;
			pam.sprite[j].que = sp_que;
			pam.sprite[j].hard = sp_hard;
			pam.sprite[j].prop = sp_prop;
			pam.sprite[j].warp_map = sp_warp_map;
			pam.sprite[j].warp_x = sp_warp_x;
			pam.sprite[j].warp_y = sp_warp_y;
			pam.sprite[j].parm_seq = sp_parm_seq;
			strcpy(pam.sprite[j].script, sp_script);
			pam.sprite[j].base_die = sp_base_die;
			pam.sprite[j].gold = sp_gold;
			pam.sprite[j].exp = sp_exp;
			pam.sprite[j].strength = sp_strength;
			pam.sprite[j].defense = sp_defense;
			pam.sprite[j].hitpoints = sp_hitpoints;
			pam.sprite[j].sound = sp_sound;
		    pam.sprite[j].vision = map_vision;
		    pam.sprite[j].nohit = sp_nohit;
			pam.sprite[j].touch_damage = sp_touch_damage;
			rect_copy(&pam.sprite[j].alt , &spr[1].alt);
		    return;
		}


	}


}
