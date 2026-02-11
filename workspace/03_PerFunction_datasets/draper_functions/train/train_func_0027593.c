setWaypointVisibility(int i, bool show)
{
  evaluateJS(QString("waypts[%1].%2();\n")
	     .arg(i).arg(show?"show": "hide"));
}
