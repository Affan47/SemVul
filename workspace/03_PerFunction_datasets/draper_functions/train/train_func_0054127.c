UArray_append_(UArray *self, const UArray *other)
{
	if(UArray_itemSize(self) < UArray_itemSize(other))
	{
		UArray_convertToItemType_(self, (int)UArray_itemType(other));
	}

	UArray_at_putAll_(self, self->size, other);
}
