on_spinbutton_value_changed( SPINBUTTON spinbutton )
{
	if ( ! GRIP )
	{
		before_value = fixed_start ? MIN_SPACE_BEFORE_MB : spinbutton_before .get_value() ;


		switch ( spinbutton )
		{
			case BEFORE	:
				spinbutton_after .set_value( TOTAL_MB - spinbutton_size .get_value() - before_value ) ;
				spinbutton_size .set_value( TOTAL_MB - before_value - spinbutton_after .get_value() ) ;

				break ;
			case SIZE	:
				spinbutton_after .set_value( TOTAL_MB - before_value - spinbutton_size .get_value() );
				if ( ! fixed_start )
					spinbutton_before .set_value(
						TOTAL_MB - spinbutton_size .get_value() - spinbutton_after .get_value() );

				break;
			case AFTER	:
				if ( ! fixed_start )
					spinbutton_before .set_value(
						TOTAL_MB - spinbutton_size .get_value() - spinbutton_after .get_value() );

				spinbutton_size .set_value( TOTAL_MB - before_value - spinbutton_after .get_value() ) ;

				break;
		}


		if ( ! fixed_start )
			frame_resizer_base ->set_x_start( Utils::round( spinbutton_before .get_value() / MB_PER_PIXEL ) ) ;

		frame_resizer_base ->set_x_end( 500 - Utils::round( spinbutton_after .get_value() / MB_PER_PIXEL ) ) ;

		frame_resizer_base ->Draw_Partition() ;

		Check_Change() ;
	}
}
