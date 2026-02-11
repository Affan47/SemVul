EnsureLineVisible(int lineDoc, bool enforcePolicy) {


	if (lineDoc >= wrapPending.start)
		WrapLines(wsAll);

	if (!cs.GetVisible(lineDoc)) {

		int lookLine = lineDoc;
		int lookLineLevel = pdoc->GetLevel(lookLine);
		while ((lookLine > 0) && (lookLineLevel & SC_FOLDLEVELWHITEFLAG)) {
			lookLineLevel = pdoc->GetLevel(--lookLine);
		}
		int lineParent = pdoc->GetFoldParent(lookLine);
		if (lineParent < 0) {

			lineParent = pdoc->GetFoldParent(lineDoc);
		}
		if (lineParent >= 0) {
			if (lineDoc != lineParent)
				EnsureLineVisible(lineParent, enforcePolicy);
			if (!cs.GetExpanded(lineParent)) {
				cs.SetExpanded(lineParent, 1);
				ExpandLine(lineParent);
			}
		}
		SetScrollBars();
		Redraw();
	}
	if (enforcePolicy) {
		int lineDisplay = cs.DisplayFromDoc(lineDoc);
		if (visiblePolicy & VISIBLE_SLOP) {
			if ((topLine > lineDisplay) || ((visiblePolicy & VISIBLE_STRICT) && (topLine + visibleSlop > lineDisplay))) {
				SetTopLine(Platform::Clamp(lineDisplay - visibleSlop, 0, MaxScrollPos()));
				SetVerticalScrollPos();
				Redraw();
			} else if ((lineDisplay > topLine + LinesOnScreen() - 1) ||
			        ((visiblePolicy & VISIBLE_STRICT) && (lineDisplay > topLine + LinesOnScreen() - 1 - visibleSlop))) {
				SetTopLine(Platform::Clamp(lineDisplay - LinesOnScreen() + 1 + visibleSlop, 0, MaxScrollPos()));
				SetVerticalScrollPos();
				Redraw();
			}
		} else {
			if ((topLine > lineDisplay) || (lineDisplay > topLine + LinesOnScreen() - 1) || (visiblePolicy & VISIBLE_STRICT)) {
				SetTopLine(Platform::Clamp(lineDisplay - LinesOnScreen() / 2 + 1, 0, MaxScrollPos()));
				SetVerticalScrollPos();
				Redraw();
			}
		}
	}
}
