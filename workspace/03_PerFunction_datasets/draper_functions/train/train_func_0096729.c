operator==(const ToolbarPrefs& other)
{
	return id == other.id &&
	       name == other.name &&
	       keys == other.keys &&
	       dock == other.dock &&

	       on == other.on &&
	       locked == other.locked &&


	       nl == other.nl;

}
