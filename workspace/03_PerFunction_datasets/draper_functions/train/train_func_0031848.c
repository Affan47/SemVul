check_sprite_right_goal_collision(int x1, int y1, int code1, int flipy1, int goalpost_only)
{
	int collided = 0;


	x1 = 240 - x1;
	y1 = 240 - y1;


	if (((y1 + 16) > GOAL_Y) && (y1 < (GOAL_Y + GOAL_HEIGHT)) &&
	    ((x1 + 16) > RIGHT_GOAL_X) && (x1 < (RIGHT_GOAL_X + GOAL_WIDTH)))
	{
		int x,y;
		int x2,y2;


		x2 = RIGHT_GOAL_X;
		y2 = GOAL_Y;

		normalize_coordinates(&x1, &y1, &x2, &y2);

		fillbitmap(sprite_goal_collision_bitmap1, Machine->pens[0], 0);
		fillbitmap(sprite_goal_collision_bitmap2, Machine->pens[0], 0);

		drawgfx(sprite_goal_collision_bitmap1,Machine->gfx[0],
				code1,1,
				0,flipy1,
				x1,y1,
				0,TRANSPARENCY_PEN,0);

		drawgfxzoom(sprite_goal_collision_bitmap2,Machine->gfx[1],
					0,1,
					1,0,
					x2,y2,
					0,TRANSPARENCY_PEN,0,
					0x20000,0x20000);

		for (x = x1; x < x1 + SPRITE_WIDTH; x++)
		{
			for (y = y1; y < y1 + SPRITE_HEIGHT; y++)
			{
				if ((read_pixel(sprite_goal_collision_bitmap1, x, y) == Machine->pens[1]))
				{
					pen_t pix = read_pixel(sprite_goal_collision_bitmap2, x, y);

					if (pix == Machine->pens[RIGHT_GOAL_COLOR])
					{
						collided = 1;
						break;
					}

					if (!goalpost_only && (pix == Machine->pens[SCORE_COLOR]))
					{
						collided = 2;
						break;
					}
				}
			}
		}
	}

	return collided;
}
