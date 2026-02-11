axis_add_grid() {
	for (int i = 1; i <= 2; i++) {
		if (xxgrid[i]) {
			double len = axis_horizontal(i) ? ylength : xlength;
			if (!xx[i].hasGridOnTop()) xx[i].setGrid(true);
			xx[i].ticks_length = len;
			xx[i+2].ticks_off = true;
			if (xx[i].subticks_length == 0.0) {
				xx[i].subticks_length = len;
				xx[i+2].subticks_off = true;
			}
			if (!xx[i].has_subticks_onoff) {

				if (xx[i].log) {
					xx[i].subticks_off = false;
				} else {
					xx[i].subticks_off = true;
				}
			}
		}
	}
}
