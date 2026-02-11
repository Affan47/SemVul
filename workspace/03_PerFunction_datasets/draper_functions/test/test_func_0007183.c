__ecereMethod___ecereNameSpace__ecere__gfx__drivers__OpenGLDisplayDriver_AllocateIndices(struct __ecereNameSpace__ecere__com__Instance * displaySystem, int nIndices, unsigned int indices32bit)
{
struct __ecereNameSpace__ecere__gfx__drivers__OGLIndices * oglIndices = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__gfx__drivers__OGLIndices);

if(oglIndices)
{
oglIndices->indices = (void *)(indices32bit ? __ecereNameSpace__ecere__com__eSystem_New(sizeof(unsigned int) * (nIndices)) : __ecereNameSpace__ecere__com__eSystem_New(sizeof(unsigned short) * (nIndices)));
__ecereNameSpace__ecere__gfx__drivers__GLGenBuffers(1, &oglIndices->buffer);
oglIndices->nIndices = nIndices;
}
return oglIndices;
}
