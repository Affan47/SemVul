button_info_do(button_info *bi)
{
	for (int i = 0; i < CCFG_MAX; i++) {
		if( button_info_query(bi, i) ) {
			int keyHasBeenUsed = FALSE;

			if( !keyHasBeenUsed ) {
				keyHasBeenUsed = button_function_demo_valid(i);
			}

			if( !keyHasBeenUsed ) {
				keyHasBeenUsed = button_function(i);
			}

			if( keyHasBeenUsed ) {
				button_info_unset(bi, i);
			}
		}
	}
}
