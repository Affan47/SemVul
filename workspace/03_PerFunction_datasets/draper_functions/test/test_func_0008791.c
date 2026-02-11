act2_fill_chinfo(const struct devmodule* dev, int stype,
	                     unsigned int ich, struct egd_chinfo* info)
{
	if (stype != EGD_TRIGGER) {
		info->isint = 0;
		info->dtype = EGD_DOUBLE;
		info->min.valdouble = -262144.0;
		info->max.valdouble = 262143.96875;
		info->label = (stype == EGD_EEG) ?
					eeg64label[ich] : sensorlabel[ich];
		info->unit = analog_unit;
		info->transducter = analog_transducter;
		info->prefiltering = get_act2(dev)->prefiltering;
	} else {
		info->isint = 1;
		info->dtype = EGD_INT32;
		info->min.valint32_t = -8388608;
		info->max.valint32_t = 8388607;
		info->label = trigglabel;
		info->unit = trigger_unit;
		info->transducter = trigger_transducter;
		info->prefiltering = trigg_prefiltering;
	}
}
