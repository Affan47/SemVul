_dxf_QueryDisplayList(HashTable ht, xfieldP xf, int buttonUp)
{
    DLKeyS key;
    DLHashP ptr;

    if (! ht)
        return NULL;

    key.tag       = DXGetObjectTag((dxObject)xf->field);
    key.approx    = buttonUp ?
			xf->attributes.buttonUp.approx :
			xf->attributes.buttonDown.approx;
    key.density   = buttonUp ?
			xf->attributes.buttonUp.density :
			xf->attributes.buttonDown.density;
    key.linewidth = xf->attributes.linewidth;
    key.aalines   = xf->attributes.aalines;

    ptr = (DLHashP)DXQueryHashElement(ht, (Pointer)&key);
    if (ptr)
    {
        ptr->hit++;
	return ptr->obj;
    }
    else
        return NULL;
}
