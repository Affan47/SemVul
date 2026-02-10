checkValid(const Polygon *g)
{
	checkInvalidCoordinates(g);
	if (validErr != NULL) return;

	checkClosedRings(g);
	if (validErr != NULL) return;

	GeometryGraph graph(0,g);

	checkTooFewPoints(&graph);
	if (validErr!=NULL) return;

	checkConsistentArea(&graph);
	if (validErr!=NULL) return;

	if (!isSelfTouchingRingFormingHoleValid) {
		checkNoSelfIntersectingRings(&graph);
		if (validErr!=NULL) return;
	}

	checkHolesInShell(g,&graph);
	if (validErr!=NULL) return;

	checkHolesNotNested(g,&graph);
	if (validErr!=NULL) return;

	checkConnectedInteriors(graph);
}
