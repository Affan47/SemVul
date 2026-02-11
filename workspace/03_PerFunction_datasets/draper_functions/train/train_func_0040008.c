ReleaseEntity()
{
	for ( u32 i = 0; i!= Entity.size(); ++i )
	{
		Entity[i].VarGroup->drop();
	}
	Entity.clear();
}
