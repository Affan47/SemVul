QueueStyling(int upTo) {
	Editor::QueueStyling(upTo);
	if (!styleNeeded.active) {

		styleNeeded.active = true;
		g_idle_add_full(G_PRIORITY_HIGH_IDLE,
			reinterpret_cast<GSourceFunc>(StyleIdle), this, NULL);
	}
}
