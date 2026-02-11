_deleteTexture(Pointer p)
{
    if (p)
    {
	Texture t = (Texture)p;
	if (t->myPixels)
	    DXFree((Pointer)t->pixels);
	if (t->textureObj)
	    DXDelete(t->textureObj);
    }
    return OK;
}
