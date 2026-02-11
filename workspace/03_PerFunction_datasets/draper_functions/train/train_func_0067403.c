gdip_propertyitems_clone(PropertyItem *src, PropertyItem **dest, int count)
{
	PropertyItem	*result;
	int		i;
	int		j;

	if (dest == NULL) {
		return InvalidParameter;
	}

	if (src == NULL) {
		*dest = NULL;
		return Ok;
	}
	result = GdipAlloc(sizeof(PropertyItem) * count);
	if (result == NULL) {
		return OutOfMemory;
	}

	for (i = 0; i < count; i++) {
		result[i].id = src[i].id;
		result[i].length = src[i].length;
		result[i].type = src[i].type;
		if ((src[i].value != NULL) && (src[i].length > 0)) {
			result[i].value = GdipAlloc(src[i].length);
			if (result[i].value == NULL) {
				for (j = 0; j < i; j++) {
					if (result[j].value != NULL) {
						GdipFree(result[j].value);
					}
				}
				GdipFree (result);
				return OutOfMemory;
			}
			memcpy(result[i].value, src[i].value, src[i].length);
		} else {
			result[i].value = NULL;
		}
	}

	*dest = result;
	return Ok;
}
