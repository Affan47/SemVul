set_slot_everywhere (MonoCompileGC *gcfg, int slot, GCSlotType type)
{
	int width, pos;
	guint8 *ref_bitmap, *pin_bitmap;


	ref_bitmap = gcfg->stack_ref_bitmap;
	pin_bitmap = gcfg->stack_pin_bitmap;
	width = gcfg->stack_bitmap_width;
	pos = width * slot;

	if (type == SLOT_PIN) {
		memset (ref_bitmap + pos, 0, width);
		memset (pin_bitmap + pos, 0xff, width);
	} else if (type == SLOT_REF) {
		memset (ref_bitmap + pos, 0xff, width);
		memset (pin_bitmap + pos, 0, width);
	} else if (type == SLOT_NOREF) {
		memset (ref_bitmap + pos, 0, width);
		memset (pin_bitmap + pos, 0, width);
	}
}
