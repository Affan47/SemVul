__ecereMethod___ecereNameSpace__ecere__gfx3D__Mesh_UnlockPrimitive(struct __ecereNameSpace__ecere__gfx3D__Mesh * this, struct __ecereNameSpace__ecere__gfx3D__PrimitiveSingle * primitive)
{
if(this && primitive)
{
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, void *  indices, unsigned int indices32bit, int nIndices))this->driver->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gfx__DisplayDriver_UnlockIndices])(this->displaySystem, primitive->data, ((unsigned int)((primitive->type & 0x200) >> 9)), primitive->nIndices);
}
}
