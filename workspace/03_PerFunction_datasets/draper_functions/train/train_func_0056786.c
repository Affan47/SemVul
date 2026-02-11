dropMap ()
{
	IVideoDriver * driver = Game->Device->getVideoDriver();

	driver->removeAllHardwareBuffers ();
	driver->removeAllTextures ();

	Player[0].shutdown ();


	dropElement ( ItemParent );
	dropElement ( ShaderParent );
	dropElement ( UnresolvedParent );
	dropElement ( FogParent );
	dropElement ( BulletParent );


	Impacts.clear();

	if ( Meta )
	{
		Meta = 0;
	}

	dropElement ( MapParent );
	dropElement ( SkyNode );


	IMeshCache *cache = Game->Device->getSceneManager ()->getMeshCache();
	cache->clear ();
	Mesh = 0;
}
