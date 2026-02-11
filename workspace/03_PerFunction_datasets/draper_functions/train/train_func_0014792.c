search_selected(gchar *str)
{
	gchar *euc_str;
	gint method;
	glong len;

	LOG(LOG_DEBUG, "IN : search_selected(%s)", str);

	if(selection_mode <= SELECTION_DO_NOTHING) {
		LOG(LOG_DEBUG, "OUT : search_selected() = NOP1");
		return;
	}

	if(strcmp(previous, str) == 0){

		LOG(LOG_DEBUG, "same as before");
		;
	} else {

		euc_str = iconv_convert("utf-8", "euc-jp", str);
		if(validate_euc_str(euc_str) == FALSE) {
			g_free(euc_str);
			LOG(LOG_DEBUG, "OUT : search_selected() = INVALID");
			return;
		}
		remove_space(euc_str);

		len = g_utf8_strlen(str, -1);

		if((auto_minchar <= len) && (len <= auto_maxchar)) {
			gtk_entry_set_text(GTK_ENTRY(word_entry), str);

			method = ebook_search_method();
			if((method == SEARCH_METHOD_INTERNET) ||
			   (method == SEARCH_METHOD_MULTI) ||
			   (method == SEARCH_METHOD_FULL_TEXT)){
				LOG(LOG_DEBUG, "OUT : search_selected() = NOP2");
				return;
			}

			if(selection_mode <= SELECTION_COPY_ONLY) {
				LOG(LOG_DEBUG, "OUT : search_selected() = COPY");
				return;
			}

			clear_message();
			clear_search_result();

			if(method == SEARCH_METHOD_GREP){
				grep_search(euc_str);
				show_result_tree();
				select_first_item();
				if(selection_mode == SELECTION_SEARCH_TOP)
					bring_to_top(main_window);
				save_word_history(str);
			} else {
				ebook_search_auto(euc_str, method);
				if(search_result){
					if(selection_mode == SELECTION_POPUP) {
						show_result_in_popup();
					} else {
						show_result_tree();
						select_first_item();
						if(selection_mode == SELECTION_SEARCH_TOP)
							bring_to_top(main_window);
					}
					save_word_history(str);
				} else {
					current_in_result = NULL;
					set_current_result(NULL);
					if(selection_mode == SELECTION_POPUP) {
						beep();
					} else {
						if(selection_mode == SELECTION_SEARCH_TOP)
							bring_to_top(main_window);
						push_message(_("No hit."));
					}
				}
			}

			sprintf(previous, "%s", str);
		} else {
			LOG(LOG_DEBUG, "OUT : search_selected() = LENGTH");
		}
		g_free(euc_str);
	}

	LOG(LOG_DEBUG, "OUT : search_selected()");
}
