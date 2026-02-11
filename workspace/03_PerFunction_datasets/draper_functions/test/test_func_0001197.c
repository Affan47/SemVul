__ecereMethod___ecereNameSpace__ecere__gfx__drivers__OpenGLDisplayDriver_UnlockMesh(struct __ecereNameSpace__ecere__com__Instance * displaySystem, struct __ecereNameSpace__ecere__gfx3D__Mesh * mesh, unsigned int flags)
{
struct __ecereNameSpace__ecere__gfx__drivers__OGLMesh * oglMesh = mesh->data;

if(!flags)
flags = __ecereProp___ecereNameSpace__ecere__gfx3D__Mesh_Get_flags(mesh);
if(__ecereNameSpace__ecere__gfx__drivers__vboAvailable)
{
if(!((unsigned int)((flags & 0x1) >> 0)) || oglMesh->vertices)
{
__ecereNameSpace__ecere__gfx__drivers__GLBindBuffer(0x8892, oglMesh->vertices);
__ecereNameSpace__ecere__gfx__drivers__GLBufferData(((unsigned int)((__ecereProp___ecereNameSpace__ecere__gfx3D__Mesh_Get_flags(mesh) & 0x20) >> 5)) ? 0x140A : 0x1406, 0x8892, __ecereProp___ecereNameSpace__ecere__gfx3D__Mesh_Get_nVertices(mesh) * (((unsigned int)((__ecereProp___ecereNameSpace__ecere__gfx3D__Mesh_Get_flags(mesh) & 0x20) >> 5)) ? sizeof(struct __ecereNameSpace__ecere__gfx3D__Vector3D) : sizeof(struct __ecereNameSpace__ecere__gfx3D__Vector3Df)), __ecereProp___ecereNameSpace__ecere__gfx3D__Mesh_Get_vertices(mesh), 0x88E4);
}
if(!((unsigned int)((flags & 0x2) >> 1)) || oglMesh->normals)
{
__ecereNameSpace__ecere__gfx__drivers__GLBindBuffer(0x8892, oglMesh->normals);
__ecereNameSpace__ecere__gfx__drivers__GLBufferData(((unsigned int)((__ecereProp___ecereNameSpace__ecere__gfx3D__Mesh_Get_flags(mesh) & 0x10) >> 4)) ? 0x140A : 0x1406, 0x8892, __ecereProp___ecereNameSpace__ecere__gfx3D__Mesh_Get_nVertices(mesh) * (((unsigned int)((__ecereProp___ecereNameSpace__ecere__gfx3D__Mesh_Get_flags(mesh) & 0x10) >> 4)) ? sizeof(struct __ecereNameSpace__ecere__gfx3D__Vector3D) : sizeof(struct __ecereNameSpace__ecere__gfx3D__Vector3Df)), __ecereProp___ecereNameSpace__ecere__gfx3D__Mesh_Get_normals(mesh), 0x88E4);
}
if(!((unsigned int)((flags & 0x4) >> 2)) || oglMesh->texCoords)
{
__ecereNameSpace__ecere__gfx__drivers__GLBindBuffer(0x8892, oglMesh->texCoords);
__ecereNameSpace__ecere__gfx__drivers__GLBufferData(0x1406, 0x8892, __ecereProp___ecereNameSpace__ecere__gfx3D__Mesh_Get_nVertices(mesh) * sizeof(struct __ecereNameSpace__ecere__sys__Pointf), __ecereProp___ecereNameSpace__ecere__gfx3D__Mesh_Get_texCoords(mesh), 0x88E4);
}
if(!((unsigned int)((flags & 0x40) >> 6)) || oglMesh->colors)
{
__ecereNameSpace__ecere__gfx__drivers__GLBindBuffer(0x8892, oglMesh->colors);
__ecereNameSpace__ecere__gfx__drivers__GLBufferData(0x1406, 0x8892, __ecereProp___ecereNameSpace__ecere__gfx3D__Mesh_Get_nVertices(mesh) * sizeof(struct __ecereNameSpace__ecere__gfx__ColorRGBAf), __ecereProp___ecereNameSpace__ecere__gfx3D__Mesh_Get_colors(mesh), 0x88E4);
}
__ecereNameSpace__ecere__gfx__drivers__GLBindBuffer(0x8892, 0);
}
}
