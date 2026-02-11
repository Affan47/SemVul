free_input_config_item_list(input_config_item *items) {
    for (input_config_item *item = items; item->config_key; item++) {
        free(item->config_key);
        free(item->config_value);
    }
    free(items);
}
