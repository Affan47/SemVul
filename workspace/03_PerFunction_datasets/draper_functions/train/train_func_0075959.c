FT_Stroker_ConicTo(FT_Stroker *stroker, GF_Point2D*  control, GF_Point2D * to)
{
	s32 error = 0;
    GF_Point2D   bez_stack[34];
    GF_Point2D*  arc;
    GF_Point2D*  limit = bez_stack + 30;
    Fixed start_angle;
    Bool first_arc = 1;


    arc    = bez_stack;
    arc[0] = *to;
    arc[1] = *control;
    arc[2] = stroker->center;

    while ( arc >= bez_stack ) {
		Fixed angle_in, angle_out;
		angle_in = angle_out = 0;

		if ( arc < limit                                             &&
			!ft_conic_is_small_enough( arc, &angle_in, &angle_out ) )
		{
			ft_conic_split( arc );
			arc += 2;
			continue;
		}

		if ( first_arc ) {
			first_arc = 0;

			start_angle = angle_in;


			if ( stroker->first_point )
				error = ft_stroker_subpath_start( stroker, start_angle );
			else {
				stroker->angle_out = start_angle;
				error = ft_stroker_process_corner( stroker );
			}
		}


		{
			GF_Point2D  ctrl, end;
			Fixed theta, phi, rotate;
			Fixed length;
			s32 side;

			theta  = gf_angle_diff( angle_in, angle_out ) / 2;
			phi    = angle_in + theta;
			length = gf_divfix( stroker->radius, gf_cos( theta ) );

			for ( side = 0; side <= 1; side++ ) {
				rotate = FT_SIDE_TO_ROTATE( side );


				ctrl = gf_v2d_from_polar(length, phi + rotate );
				ctrl.x += arc[1].x;
				ctrl.y += arc[1].y;


				end = gf_v2d_from_polar(stroker->radius, angle_out + rotate );
				end.x += arc[0].x;
				end.y += arc[0].y;

				error = ft_stroke_border_conicto( stroker->borders + side, &ctrl, &end );
				if ( error )
					goto Exit;
			}
		}

		arc -= 2;

		if ( arc < bez_stack )
			stroker->angle_in = angle_out;
    }

    stroker->center = *to;
Exit:
    return error;
}
