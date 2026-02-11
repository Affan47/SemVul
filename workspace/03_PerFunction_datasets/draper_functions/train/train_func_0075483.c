NullTextureTarget(NullRenderer& owner) :
    NullRenderTarget(owner),
    d_CEGUITexture(0)
{
    d_CEGUITexture = static_cast<NullTexture*>(&d_owner.createTexture());


    declareRenderSize(Size(DEFAULT_SIZE, DEFAULT_SIZE));
}
