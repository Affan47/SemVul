get_dataset_ranges() {

	reset_axis_ranges();

	if (g_colormap != NULL && g_colormap->getData() != NULL) {
		GLERectangle* bounds = g_colormap->getData()->getBounds();
		bounds->addToRangeX(xx[GLE_AXIS_X].getDataRange());
		bounds->addToRangeY(xx[GLE_AXIS_Y].getDataRange());
	}

	for (int bar = 1; bar <= g_nbar; bar++) {
		for (int i = 0; i < br[bar]->ngrp; i++) {
			int to_bar = br[bar]->to[i];
			if (to_bar != 0 && to_bar <= ndata && dp[to_bar] != NULL && dp[to_bar]->np > 0) {


				int np = dp[to_bar]->np;
				if (np > 0) {
					GLEDataSetDimension* xdim = dp[to_bar]->getDimXInv();
					GLERange* xrange = xx[xdim->getAxis()].getDataRange();
					GLEDataPairs barData(dp[to_bar]);
					double delta = barData.getMinXInterval();
					xrange->updateRange(barData.getX(0) - delta/2, barData.getM(0));
					xrange->updateRange(barData.getX(np - 1) + delta/2, barData.getM(np-1));
				}
			}
		}
	}

	for (int axis = GLE_AXIS_X; axis <= GLE_AXIS_Y0; axis++) {
		GLEAxis* ax = &xx[axis];
		if (!ax->getRange()->hasBoth()) {
			if (ax->shouldPerformQuantileScale()) {
				quantile_scale(ax);
			} else {
				min_max_scale(ax);
			}
		}
	}
}
