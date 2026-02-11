setActiveTexture(u32 stage, video::ITexture* texture)
{
	if (texture && texture->getDriverType() != EDT_SOFTWARE)
	{
		os::Printer::log("Fatal Error: Tried to set a texture not owned by this driver.", ELL_ERROR);
		return false;
	}

	if (Texture)
		Texture->drop();

	Texture = texture;

	if (Texture)
		Texture->grab();

	selectRightTriangleRenderer();
	return true;
}
