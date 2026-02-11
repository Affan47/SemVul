__ecereMethod___ecereNameSpace__ecere__gfx__drivers__OpenGLDisplayDriver_ApplyMaterial(struct __ecereNameSpace__ecere__com__Instance * display, struct __ecereNameSpace__ecere__gfx3D__Material * material, struct __ecereNameSpace__ecere__gfx3D__Mesh * mesh)
{
if(((unsigned int)((material->flags & 0x1) >> 0)))
{
glLightModeli(0x0B52, !((unsigned int)((material->flags & 0x10) >> 4)));
glDisable(0x0B44);
}
else
{
glLightModeli(0x0B52, (unsigned int)0x0);
glEnable(0x0B44);
}
if(((unsigned int)((material->flags & 0x8) >> 3)))
glDisable(0x0B60);
else
glEnable(0x0B60);
if(material->baseMap && __ecereProp___ecereNameSpace__ecere__gfx3D__Mesh_Get_texCoords(mesh))
{
struct __ecereNameSpace__ecere__com__Instance * map = material->baseMap;

glEnable(0x0DE1);
glBindTexture(0x0DE1, (unsigned int)((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)map + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->driverData);
if(((unsigned int)((material->flags & 0x4) >> 2)))
{
glTexParameteri(0x0DE1, 0x2802, 0x2901);
glTexParameteri(0x0DE1, 0x2803, 0x2901);
}
else
{
glTexParameteri(0x0DE1, 0x2802, 0x812F);
glTexParameteri(0x0DE1, 0x2803, 0x812F);
}
}
else
glDisable(0x0DE1);
if(((unsigned int)((__ecereProp___ecereNameSpace__ecere__gfx3D__Mesh_Get_flags(mesh) & 0x40) >> 6)))
{
glColorMaterial(0x0408, 0x1602);
glEnable(0x0B57);
}
else
{
glDisable(0x0B57);
{
float color[4] =
{
material->diffuse.r, material->diffuse.g, material->diffuse.b, material->opacity
};

glMaterialfv(0x0408, 0x1201, color);
}
{
float color[4] =
{
material->ambient.r, material->ambient.g, material->ambient.b, 0
};

glMaterialfv(0x0408, 0x1200, color);
}
}
{
float color[4] =
{
material->specular.r, material->specular.g, material->specular.b, 0
};

glMaterialfv(0x0408, 0x1202, color);
}
{
float color[4] =
{
material->emissive.r, material->emissive.g, material->emissive.b, 0
};

glMaterialfv(0x0408, 0x1600, color);
}
glMaterialfv(0x0408, 0x1601, &material->power);
}
