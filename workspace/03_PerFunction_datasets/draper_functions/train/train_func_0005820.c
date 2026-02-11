scarlett_ctl_enum_resume(struct usb_mixer_elem_list *list)
{
	struct usb_mixer_elem_info *elem =
		container_of(list, struct usb_mixer_elem_info, head);

	if (elem->cached)
		snd_usb_set_cur_mix_value(elem, 0, 0, *elem->cache_val);
	return 0;
}
