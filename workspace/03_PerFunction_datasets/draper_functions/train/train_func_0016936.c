register_item_check(const string& check_name, item_check_fun item_check) {
        if (!was_performed(check_name)) {
            item_checks[check_name] = item_check;
        }
    }
