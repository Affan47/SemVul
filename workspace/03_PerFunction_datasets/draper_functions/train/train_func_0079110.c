CheckBulletCollisions(int num)
{
	Bullet CurBullet = &AllBullets[num];

	switch (CurBullet->type) {
	case INFOUT:

		return;
		break;

	default:


		check_bullet_player_collisions(CurBullet, num);
		if (CurBullet->type == INFOUT)
			return;


		gps bullet_actual_pos = CurBullet->pos;
		struct visible_level *visible_lvl, *next_lvl;

		BROWSE_VISIBLE_LEVELS(visible_lvl, next_lvl) {
			level *lvl = visible_lvl->lvl_pointer;


			update_virtual_position(&CurBullet->pos, &bullet_actual_pos, lvl->levelnum);
			if (CurBullet->pos.x == -1)
				continue;


			if (!pos_near_level(CurBullet->pos.x, CurBullet->pos.y, lvl, DROIDHITDIST))
				continue;


			check_bullet_background_collisions(CurBullet, num);
			if (CurBullet->type == INFOUT)
				return;

			check_bullet_enemy_collisions(CurBullet, num);
			if (CurBullet->type == INFOUT)
				return;
		}


		CurBullet->pos.x = bullet_actual_pos.x;
		CurBullet->pos.y = bullet_actual_pos.y;
		CurBullet->pos.z = bullet_actual_pos.z;

		break;
	}
}
