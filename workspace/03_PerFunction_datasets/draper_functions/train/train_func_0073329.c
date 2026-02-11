__ecereMethod___ecereNameSpace__ecere__gfx3D__Camera_Move(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__gfx3D__Vector3D * direction)
{
struct __ecereNameSpace__ecere__gfx3D__Camera * __ecerePointer___ecereNameSpace__ecere__gfx3D__Camera = (struct __ecereNameSpace__ecere__gfx3D__Camera *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gfx3D__Camera->offset) : 0);
struct __ecereNameSpace__ecere__gfx3D__Matrix matrix;

switch(__ecerePointer___ecereNameSpace__ecere__gfx3D__Camera->type)
{
case 0:
{
struct __ecereNameSpace__ecere__gfx3D__Vector3D offset;

__ecereMethod___ecereNameSpace__ecere__gfx3D__Matrix_RotationQuaternion(&matrix, &__ecerePointer___ecereNameSpace__ecere__gfx3D__Camera->orientation);
__ecereMethod___ecereNameSpace__ecere__gfx3D__Vector3D_MultMatrix(&offset, direction, &matrix);
__ecereMethod___ecereNameSpace__ecere__gfx3D__Vector3D_Add(&__ecerePointer___ecereNameSpace__ecere__gfx3D__Camera->position, &__ecerePointer___ecereNameSpace__ecere__gfx3D__Camera->position, &offset);
break;
}
case 3:
case 2:
case 4:
{
__ecereMethod___ecereNameSpace__ecere__gfx3D__Vector3D_Add(&__ecerePointer___ecereNameSpace__ecere__gfx3D__Camera->position, &__ecerePointer___ecereNameSpace__ecere__gfx3D__Camera->position, direction);
break;
}
}
}
