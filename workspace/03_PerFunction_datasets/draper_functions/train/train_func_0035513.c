__ecereMethod___ecereNameSpace__ecere__gfx3D__Camera_Untransform(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__gfx3D__Vector3D * src, struct __ecereNameSpace__ecere__gfx3D__Vector3D * result)
{
struct __ecereNameSpace__ecere__gfx3D__Camera * __ecerePointer___ecereNameSpace__ecere__gfx3D__Camera = (struct __ecereNameSpace__ecere__gfx3D__Camera *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gfx3D__Camera->offset) : 0);

__ecereMethod___ecereNameSpace__ecere__gfx3D__Vector3D_MultMatrix(result, src, &__ecerePointer___ecereNameSpace__ecere__gfx3D__Camera->inverseMatrix);
result->x += __ecerePointer___ecereNameSpace__ecere__gfx3D__Camera->cPosition.x;
result->y += __ecerePointer___ecereNameSpace__ecere__gfx3D__Camera->cPosition.y;
result->z += __ecerePointer___ecereNameSpace__ecere__gfx3D__Camera->cPosition.z;
}
