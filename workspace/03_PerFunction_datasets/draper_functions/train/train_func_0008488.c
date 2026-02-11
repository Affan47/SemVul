fbcon_fb_unbind(int idx)
{
	int i, new_idx = -1, ret = 0;

	if (!fbcon_has_console_bind)
		return 0;

	for (i = first_fb_vc; i <= last_fb_vc; i++) {
		if (con2fb_map[i] != idx &&
		    con2fb_map[i] != -1) {
			new_idx = i;
			break;
		}
	}

	if (new_idx != -1) {
		for (i = first_fb_vc; i <= last_fb_vc; i++) {
			if (con2fb_map[i] == idx)
				set_con2fb_map(i, new_idx, 0);
		}
	} else {
		struct fb_info *info = registered_fb[idx];


		for (i = first_fb_vc; i <= last_fb_vc; i++) {
			if (con2fb_map[i] == idx) {
				con2fb_map[i] = -1;
				if (!search_fb_in_map(idx)) {
					ret = con2fb_release_oldinfo(vc_cons[i].d,
								     info, NULL, i,
								     idx, 0);
					if (ret) {
						con2fb_map[i] = idx;
						return ret;
					}
				}
			}
		}
		ret = fbcon_unbind();
	}

	return ret;
}
