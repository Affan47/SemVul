decode_8bit(Array encodedImage)
{
 Field pixField = NULL;
 Array a = NULL;
 int i, j, image_size, flag, knt;
 ubyte *ptr = (ubyte *)DXGetArrayData(encodedImage);
 int *res, x, y;
 ubyte *pix;

 a = (Array)DXGetAttribute((Object)encodedImage, "resolution");
 if (! a)
 {
 DXSetError(ERROR_INTERNAL,
 "cached image missing resolution attrbute");
 goto error;
 }

 res = DXGetArrayData(a);
 x = res[0]; y = res[1];

 pixField = DXNewField();
 if (! pixField)
 goto error;

 a = DXMakeGridPositions(2, x, y, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0);
 if (! a)
 goto error;

 if (! DXSetComponentValue(pixField, POSITIONS, (Object)a))
 goto error;

 a = DXMakeGridConnections(2, x, y);
 if (! a)
 goto error;
 if (! DXSetConnections(pixField, "quads", a))
 goto error;

 a = DXNewArray(TYPE_UBYTE, CATEGORY_REAL, 0, 1);
 if (! a)
 goto error;
 if (! DXAddArrayData(a, 0, x*y, NULL))
 goto error;
 if (! DXSetAttribute((Object)a, "8bit", O_X_IMAGE))
 goto error;

 pix = (ubyte *)DXGetArrayData(a);

 image_size = x*y;

 for (i = 0; i != image_size; i += knt)
 {
 flag = *ptr & 0x80;
 knt = *ptr & 0x7f;

 ptr ++;

 if (flag)
 {
 memcpy((char *)pix, (char *)ptr, sizeof(ubyte)*knt);
 (*((ubyte *)(pix)) = *((ubyte *)(ptr)));
 pix += knt*sizeof(ubyte);
 ptr += knt*sizeof(ubyte);
 } else {
 ubyte proto;
 (*((ubyte *)(&proto)) = *((ubyte *)(ptr)));
 for (j = 0; j < knt; j++)
 {
 *(ubyte *)pix = proto;
 pix += sizeof(ubyte);
 }

 ptr += sizeof(ubyte);
 }
 }

 if (! DXSetComponentValue(pixField, IMAGE, (Object)a))
 goto error;

 return DXEndField(pixField);

error:
 DXFree((Object)pixField);
 DXFree((Object)a);

 return NULL;
}
