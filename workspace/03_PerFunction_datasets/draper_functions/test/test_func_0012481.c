GdipGetAllPropertyItems (GpImage *image, UINT totalBufferSize, UINT numProperties, PropertyItem *allItems)
{
	int		size;
	int		i;
	BYTE *ptr;

	if (!image || !allItems)
		return InvalidParameter;


	if (image->type != ImageTypeBitmap)
		return NotImplemented;

	if (numProperties != image->active_bitmap->property_count) {
		return InvalidParameter;
	}

	size = image->active_bitmap->property_count * sizeof(PropertyItem);
	for (i = 0; i < numProperties; i++) {
		size += image->active_bitmap->property[i].length;
	}

	if (size != totalBufferSize) {
		return InvalidParameter;
	}

	ptr = (BYTE*)allItems;
	ptr += totalBufferSize;


	memcpy(allItems, image->active_bitmap->property, sizeof(PropertyItem) * numProperties);


	for (i = 0; i < numProperties; i++) {
		if (allItems[i].value != NULL) {
			ptr -= allItems[i].length;
			memcpy(ptr, allItems[i].value, allItems[i].length);
			allItems[i].value = ptr;
		}
	}

	return Ok;
}
