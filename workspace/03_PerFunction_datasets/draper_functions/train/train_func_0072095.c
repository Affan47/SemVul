eng_get_next_zone(gint32 frame_id, gint32 * x, gint32 * y, gint32 * width, gint32 * height){

	gint32 i, x1, y1, x2 ,y2;

	for(i = 0 ; i < frame[frame_id]->nb_zone ; i++) {

		if(frame[frame_id]->zone_upd[i]->y2 > 0)  {

			x1 = frame[frame_id]->zone_upd[i]->x1;
			y1 = frame[frame_id]->zone_upd[i]->y1;
			x2 = frame[frame_id]->zone_upd[i]->x2;
			y2 = frame[frame_id]->zone_upd[i]->y2;
			frame[frame_id]->zone_upd[i]->y2 = 0;

			*x = x1;
			*y = y1;
			*width = x2 -x1 +1;
			*height = y2 -y1 +1;

			return(eng_get_zone(frame_id, x1, y1, x2, y2) );
		}
	}

	return(NULL);
}
