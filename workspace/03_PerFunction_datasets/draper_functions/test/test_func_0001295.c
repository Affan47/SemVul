grab_key_unsafe (Key             *key,
                 GsdKeygrabFlags  flags,
                 GSList          *screens)
{
        guint key_mask = get_mask_for_key (key->keysym);

        grab_key_internal (key, TRUE, flags, screens);

        if (key_mask != 0) {
                Key copy;
                guint i, j;

                if ((key->state & key_mask) != 0) {
                        guint mirror = get_mirrored_key (key->keysym);

                        if (mirror != 0) {
                                gint mirror_keys_len;
                                GdkKeymapKey *mirror_keys;

                                gdk_keymap_get_entries_for_keyval (gdk_keymap_get_default (),
                                                                   mirror,
                                                                   &mirror_keys,
                                                                   &mirror_keys_len);

                                copy.keysym = mirror;
                                copy.state = key->state;
                                copy.keycodes = g_new0 (guint, mirror_keys_len + 1);

                                for (j = 0; j < mirror_keys_len; j++)
                                        copy.keycodes[j] = mirror_keys[j].keycode;

                                grab_key_internal (&copy, TRUE, flags, screens);

                                g_free (copy.keycodes);
                                g_free (mirror_keys);
                        }
                }

                for (i = 0; i < 8 * sizeof (guint); i++) {
                        guint left, right;
                        gint left_keys_len, right_keys_len;
                        GdkKeymapKey *left_keys, *right_keys;

                        if (1 << i == key_mask || (key->state & 1 << i) == 0)
                                continue;

                        get_keys_for_bit (i, &left, &right);

                        if (left == 0 && right == 0)
                                continue;

                        left_keys_len = 0;
                        right_keys_len = 0;
                        left_keys = NULL;
                        right_keys = NULL;

                        if (left != 0)
                                gdk_keymap_get_entries_for_keyval (gdk_keymap_get_default (),
                                                                   left,
                                                                   &left_keys,
                                                                   &left_keys_len);

                        if (right != 0)
                                gdk_keymap_get_entries_for_keyval (gdk_keymap_get_default (),
                                                                   right,
                                                                   &right_keys,
                                                                   &right_keys_len);

                        copy.keysym = left != 0 ? left : right;
                        copy.state = (key->state | key_mask) & ~(1 << i);
                        copy.keycodes = g_new0 (guint, left_keys_len + right_keys_len + 1);

                        for (j = 0; j < left_keys_len; j++)
                                copy.keycodes[j] = left_keys[j].keycode;
                        for (j = 0; j < right_keys_len; j++)
                                copy.keycodes[left_keys_len + j] = right_keys[j].keycode;

                        grab_key_internal (&copy, TRUE, flags, screens);

                        g_free (copy.keycodes);
                        g_free (right_keys);
                        g_free (left_keys);
                }
        }
}
