vte_register_symbols(GModule *mod)
{
	#define BIND_SYMBOL(field) \
		g_module_symbol(mod, #field, (void*)&vf->field)
	#define BIND_REQUIRED_SYMBOL(field) \
		G_STMT_START { \
			if (! BIND_SYMBOL(field)) \
			{ \
				g_critical(_("invalid VTE library \"%s\": missing symbol \"%s\""), \
						g_module_name(mod), #field); \
				return FALSE; \
			} \
		} G_STMT_END

	BIND_REQUIRED_SYMBOL(vte_terminal_new);
	BIND_REQUIRED_SYMBOL(vte_terminal_set_size);
	BIND_REQUIRED_SYMBOL(vte_terminal_fork_command);
	BIND_REQUIRED_SYMBOL(vte_terminal_set_word_chars);
	BIND_REQUIRED_SYMBOL(vte_terminal_set_mouse_autohide);
	BIND_REQUIRED_SYMBOL(vte_terminal_reset);
	BIND_REQUIRED_SYMBOL(vte_terminal_get_type);
	BIND_REQUIRED_SYMBOL(vte_terminal_set_scroll_on_output);
	BIND_REQUIRED_SYMBOL(vte_terminal_set_scroll_on_keystroke);
	BIND_REQUIRED_SYMBOL(vte_terminal_set_font_from_string);
	BIND_REQUIRED_SYMBOL(vte_terminal_set_scrollback_lines);
	BIND_REQUIRED_SYMBOL(vte_terminal_get_has_selection);
	BIND_REQUIRED_SYMBOL(vte_terminal_copy_clipboard);
	BIND_REQUIRED_SYMBOL(vte_terminal_paste_clipboard);
	BIND_REQUIRED_SYMBOL(vte_terminal_set_emulation);
	BIND_REQUIRED_SYMBOL(vte_terminal_set_color_foreground);
	BIND_REQUIRED_SYMBOL(vte_terminal_set_color_bold);
	BIND_REQUIRED_SYMBOL(vte_terminal_set_color_background);
	BIND_REQUIRED_SYMBOL(vte_terminal_set_background_image_file);
	BIND_REQUIRED_SYMBOL(vte_terminal_feed_child);
	BIND_REQUIRED_SYMBOL(vte_terminal_im_append_menuitems);
	if (! BIND_SYMBOL(vte_terminal_set_cursor_blink_mode))


		BIND_REQUIRED_SYMBOL(vte_terminal_set_cursor_blinks);
	BIND_REQUIRED_SYMBOL(vte_terminal_select_all);
	BIND_REQUIRED_SYMBOL(vte_terminal_set_audible_bell);

	#undef BIND_REQUIRED_SYMBOL
	#undef BIND_SYMBOL

	return TRUE;
}
