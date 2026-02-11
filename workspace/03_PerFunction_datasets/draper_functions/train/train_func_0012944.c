__ecereMethod_ModelView_OnRightButtonDown(struct __ecereNameSpace__ecere__com__Instance * this, int x, int y, unsigned int mods)
{
struct ModelView * __ecerePointer_ModelView = (struct ModelView *)(this ? (((char *)this) + __ecereClass_ModelView->offset) : 0);

if(!__ecerePointer_ModelView->moving && !__ecerePointer_ModelView->lightMoving)
{
struct __ecereNameSpace__ecere__gfx3D__Euler __simpleStruct0;

__ecerePointer_ModelView->startPosition.x = x;
__ecerePointer_ModelView->startPosition.y = y;
__ecerePointer_ModelView->startOrientation = (__ecereProp___ecereNameSpace__ecere__gfx3D__Euler_Set___ecereNameSpace__ecere__gfx3D__Quaternion(&__simpleStruct0, &__ecerePointer_ModelView->light.orientation), __simpleStruct0);
__ecereMethod___ecereNameSpace__ecere__gui__Window_Capture(this);
__ecerePointer_ModelView->lightMoving = 0x1;
}
return 0x1;
}
