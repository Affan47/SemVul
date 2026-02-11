mt_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	int ret, i;
	struct mt_device *td;
	struct mt_class *mtclass = mt_classes;

	for (i = 0; mt_classes[i].name ; i++) {
		if (id->driver_data == mt_classes[i].name) {
			mtclass = &(mt_classes[i]);
			break;
		}
	}


	hdev->quirks |= HID_QUIRK_NO_INPUT_SYNC;


	hdev->quirks |= HID_QUIRK_MULTI_INPUT;
	hdev->quirks |= HID_QUIRK_NO_EMPTY_INPUT;


	if (id->group == HID_GROUP_MULTITOUCH_WIN_8)


		hdev->quirks |= HID_QUIRK_NO_INIT_REPORTS;

	td = devm_kzalloc(&hdev->dev, sizeof(struct mt_device), GFP_KERNEL);
	if (!td) {
		dev_err(&hdev->dev, "cannot allocate multitouch data\n");
		return -ENOMEM;
	}
	td->mtclass = *mtclass;
	td->inputmode = -1;
	td->maxcontact_report_id = -1;
	td->inputmode_value = MT_INPUTMODE_TOUCHSCREEN;
	td->cc_index = -1;
	td->mt_report_id = -1;
	hid_set_drvdata(hdev, td);

	td->fields = devm_kzalloc(&hdev->dev, sizeof(struct mt_fields),
				  GFP_KERNEL);
	if (!td->fields) {
		dev_err(&hdev->dev, "cannot allocate multitouch fields data\n");
		return -ENOMEM;
	}

	if (id->vendor == HID_ANY_ID && id->product == HID_ANY_ID)
		td->serial_maybe = true;

	ret = hid_parse(hdev);
	if (ret != 0)
		return ret;

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	if (ret)
		return ret;

	ret = sysfs_create_group(&hdev->dev.kobj, &mt_attribute_group);

	mt_set_maxcontacts(hdev);
	mt_set_input_mode(hdev);


	devm_kfree(&hdev->dev, td->fields);
	td->fields = NULL;

	return 0;
}
