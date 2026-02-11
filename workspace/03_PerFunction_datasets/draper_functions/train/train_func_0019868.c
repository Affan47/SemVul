major_copy_or_mark_object_canonical (GCObject **ptr, SgenGrayQueue *queue)
{
	major_copy_or_mark_object_with_evacuation (ptr, *ptr, queue);
}
