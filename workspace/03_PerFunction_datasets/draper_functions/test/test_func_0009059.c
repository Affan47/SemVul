disp_worker_hit_points(int x1, int y1, int x2, int hitPoints, int maxHitPoints)
{


	#define HIT_BAR_TYPE_COUNT  3

	int  hit_bar_color_array[HIT_BAR_TYPE_COUNT] = { 0xA8, 0xB4, 0xAC };
	int  hit_bar_max_array[HIT_BAR_TYPE_COUNT] 	= { 50, 100, 200 };
	char hitBarColor;

	for( int i=0 ; i<HIT_BAR_TYPE_COUNT ; i++ )
	{
		if( maxHitPoints <= hit_bar_max_array[i] || i==HIT_BAR_TYPE_COUNT-1 )
		{
			hitBarColor = hit_bar_color_array[i];
			break;
		}
	}


	enum { HIT_BAR_DARK_BORDER = 3,
			 HIT_BAR_BODY 		   = 1 };

	int barWidth = (x2-x1+1) * hitPoints / MAX(hitPoints, maxHitPoints);

	vga_front.bar( x1, y1, x1+barWidth-1, y1+1, hitBarColor + HIT_BAR_BODY );

	if( x1+barWidth <= x2 )
		vga_util.blt_buf( x1+barWidth, y1, x2, y1+1, 0 );

	y1+=2;

	vga_front.bar( x1, y1, x1+barWidth-1, y1, hitBarColor + HIT_BAR_DARK_BORDER );
	vga_front.bar( x1+barWidth, y1, x1+barWidth, y1, V_BLACK );

	if( x1+barWidth+1 <= x2 )
		vga_util.blt_buf( x1+barWidth+1, y1, x2, y1, 0 );

	y1++;

	vga_front.bar( x1+1, y1, x1+barWidth, y1, V_BLACK );

	if( x1+barWidth+1 <= x2 )
		vga_util.blt_buf( x1+barWidth+1, y1, x2, y1, 0 );
}
