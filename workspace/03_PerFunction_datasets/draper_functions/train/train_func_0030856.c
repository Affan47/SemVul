greaterThan(const QString & myVersionStr, const QString & yourVersionStr) {
	VersionThing myVersionThing;
	Version::toVersionThing(myVersionStr,myVersionThing);
	VersionThing yourVersionThing;
	Version::toVersionThing(yourVersionStr,yourVersionThing);
	return greaterThan(myVersionThing,yourVersionThing);
}
