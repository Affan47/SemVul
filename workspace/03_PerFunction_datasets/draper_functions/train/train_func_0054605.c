__ecereNameSpace__ecere__gfx3D__models__ReadSmoothing(struct __ecereNameSpace__ecere__gfx3D__models__FileInfo * info, struct __ecereNameSpace__ecere__com__Instance * object)
{
struct __ecereNameSpace__ecere__gfx3D__Mesh * mesh = __ecereProp___ecereNameSpace__ecere__gfx3D__Object_Get_mesh(object);

switch((*info).chunkId)
{
case 16720:
{
int c;

for(c = 0; c < (*info).nFaces; c++)
(*info).faces[c].smoothGroups = __ecereNameSpace__ecere__gfx3D__models__ReadDWORD((*info).f);
break;
}
}
return 0x1;
}
