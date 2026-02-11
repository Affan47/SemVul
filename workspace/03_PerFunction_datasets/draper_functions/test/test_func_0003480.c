ft_stroker_cap(FT_Stroker  *stroker, Fixed angle, s32 side)
{
    s32 error  = 0;
    if ( stroker->line_cap == GF_LINE_CAP_ROUND) {


		GF_Point2D delta, delta2, ctl1, ctl2, end;
		Fixed rotate = FT_SIDE_TO_ROTATE( side );
		Fixed radius = stroker->radius;
		FT_StrokeBorder  border = stroker->borders + side;


		delta = gf_v2d_from_polar(radius, angle);
		delta.x = 4*delta.x/3;
		delta.y = 4*delta.y/3;

		delta2 = gf_v2d_from_polar(radius, angle + rotate);
		ctl1.x = delta.x + stroker->center.x + delta2.x;
		ctl1.y = delta.y + stroker->center.y + delta2.y;

		delta2 = gf_v2d_from_polar(radius, angle - rotate);
		ctl2.x = delta.x + delta2.x + stroker->center.x;
		ctl2.y = delta.y + delta2.y + stroker->center.y;

		end.x = delta2.x + stroker->center.x;
		end.y = delta2.y + stroker->center.y;

		error = ft_stroke_border_cubicto( border, &ctl1, &ctl2, &end);
	} else if ( stroker->line_cap == GF_LINE_CAP_SQUARE) {

		GF_Point2D        delta, delta2;
		Fixed rotate = FT_SIDE_TO_ROTATE( side );
		Fixed radius = stroker->radius;
		FT_StrokeBorder  border = stroker->borders + side;


		delta2 = gf_v2d_from_polar(radius, angle + rotate);
		delta = gf_v2d_from_polar(radius, angle);

		delta.x += stroker->center.x + delta2.x;
		delta.y += stroker->center.y + delta2.y;

		error = ft_stroke_border_lineto( border, &delta, 0 );
		if ( error )
			goto Exit;

		delta2 = gf_v2d_from_polar(radius, angle - rotate);
		delta = gf_v2d_from_polar(radius, angle);

		delta.x += delta2.x + stroker->center.x;
		delta.y += delta2.y + stroker->center.y;

		error = ft_stroke_border_lineto( border, &delta, 0 );
    } else if ( stroker->line_cap == GF_LINE_CAP_TRIANGLE) {

		GF_Point2D delta;
		Fixed radius = stroker->radius;
		FT_StrokeBorder  border = stroker->borders + side;
		border->movable = 0;
		delta = gf_v2d_from_polar(radius, angle);
		delta.x += stroker->center.x;
		delta.y += stroker->center.y;
		error = ft_stroke_border_lineto(border, &delta, 0);
    }

Exit:
    return error;
}
