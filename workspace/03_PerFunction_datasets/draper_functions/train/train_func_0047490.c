logic(float dt) {

    interval_remaining -= dt;


    if(interval_remaining <= 0.0f) {

        if(show) {
            active_keys.clear();
            std::vector<FileKeyEntry*> finished_keys;

            for(std::map<std::string, FileKeyEntry*>::iterator it = keymap.begin(); it != keymap.end(); it++) {
                FileKeyEntry* entry = it->second;

                if(!entry->isFinished()) {
                    active_keys.push_back(entry);
                } else {
                    finished_keys.push_back(entry);
                }
            }


            std::sort(active_keys.begin(), active_keys.end(), file_key_entry_sort);


            int max_visible_entries = std::max(0, (int)((display.height - 150.0f) / 20.0f));

            if (active_keys.size() > max_visible_entries) {
                active_keys.resize(max_visible_entries);
            }


            float key_y = 20.0f;

            for(std::vector<FileKeyEntry*>::iterator it = active_keys.begin(); it != active_keys.end(); it++) {
                FileKeyEntry* entry = *it;
                if(entry->getCount()>0) {
                    entry->setDestY(key_y);
                }
                key_y += 20.0f;
            }


            for(std::vector<FileKeyEntry*>::iterator it = finished_keys.begin(); it != finished_keys.end(); it++) {
                FileKeyEntry* entry = *it;
                keymap.erase(entry->getExt());
                delete entry;
            }
        }

        interval_remaining = update_interval;
    }

    for(std::vector<FileKeyEntry*>::iterator it = active_keys.begin(); it != active_keys.end(); it++) {

        FileKeyEntry* entry = *it;

        entry->logic(dt);
    }
}
