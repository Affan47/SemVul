scg_queue_movement (SheetControlGUI	*scg,
		    SCGUIMoveFunc	 handler,
		    int n, gboolean jump, gboolean horiz)
{
	g_return_if_fail (IS_SHEET_CONTROL_GUI (scg));


	if (scg->delayedMovement.timer != 0) {
		if (jump ||

		    scg->delayedMovement.counter > 3 ||
		    scg->delayedMovement.handler != handler ||
		    scg->delayedMovement.horiz != horiz) {
			g_source_remove (scg->delayedMovement.timer);
			(*scg->delayedMovement.handler) (scg,
				scg->delayedMovement.n, FALSE,
				scg->delayedMovement.horiz);
			scg->delayedMovement.handler = NULL;
			scg->delayedMovement.timer = 0;
		} else {
			scg->delayedMovement.counter++;
			scg->delayedMovement.n += n;
			return;
		}
	}


	if (jump) {
		Sheet const *sheet = scg_sheet (scg);
		(*handler) (scg, n, TRUE, horiz);
		if (wbcg_is_editing (scg->wbcg))
			sheet_update_only_grid (sheet);
		else
			sheet_update (sheet);
		return;
	}

	scg->delayedMovement.counter = 1;
	scg->delayedMovement.handler = handler;
	scg->delayedMovement.horiz   = horiz;
	scg->delayedMovement.n	     = n;
	scg->delayedMovement.timer   = g_timeout_add (10,
		(GSourceFunc)cb_scg_queued_movement, scg);
}
