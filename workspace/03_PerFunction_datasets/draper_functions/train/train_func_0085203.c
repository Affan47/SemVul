CSkyDomeSceneNode(video::ITexture* sky, u32 horiRes, u32 vertRes,
		f32 texturePercentage, f32 spherePercentage, f32 radius,
		ISceneNode* parent, ISceneManager* mgr, s32 id)
	: ISceneNode(parent, mgr, id), Buffer(0),
	  HorizontalResolution(horiRes), VerticalResolution(vertRes),
	  TexturePercentage(texturePercentage),
	  SpherePercentage(spherePercentage), Radius(radius)
{
	#ifdef _DEBUG
	setDebugName("CSkyDomeSceneNode");
	#endif

	setAutomaticCulling(scene::EAC_OFF);

	Buffer = new SMeshBuffer();
	Buffer->Material.Lighting = false;
	Buffer->Material.ZBuffer = video::ECFN_NEVER;
	Buffer->Material.ZWriteEnable = false;
	Buffer->Material.AntiAliasing = video::EAAM_OFF;
	Buffer->Material.setTexture(0, sky);
	Buffer->BoundingBox.MaxEdge.set(0,0,0);
	Buffer->BoundingBox.MinEdge.set(0,0,0);

	Buffer->Vertices.clear();
	Buffer->Indices.clear();


	generateMesh();
}
