addRenderTargetTexture(const core::dimension2d<u32>& size,
		const io::path& name, const ECOLOR_FORMAT format)
{
	CImage* img = new CImage(BURNINGSHADER_COLOR_FORMAT, size);
	ITexture* tex = new CSoftwareTexture2(img, name, CSoftwareTexture2::IS_RENDERTARGET );
	img->drop();
	addTexture(tex);
	tex->drop();
	return tex;
}
