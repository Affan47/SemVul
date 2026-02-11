sensor_hub_get_physical_device_count(struct hid_device *hdev)
{
	int i;
	int count = 0;

	for (i = 0; i < hdev->maxcollection; ++i) {
		struct hid_collection *collection = &hdev->collection[i];
		if (collection->type == HID_COLLECTION_PHYSICAL ||
		    collection->type == HID_COLLECTION_APPLICATION)
			++count;
	}

	return count;
}
