removeBuilding( GenericBuilding * build )
{
	removeAnimation( dynamic_cast<Building*>(build) );
	GameData::removeBuilding( build );
}
