test_parse_objects() {

  json_Item item, *subitem;


  parse_to_item("{\"a\": \"def\"}");
  test_that(item.type == item_object);
  map__for(pair, item.value.object) {
    test_that(strcmp((char *)pair->key, "a") == 0);
    subitem = (json_Item *)pair->value;
    test_that(subitem->type == item_string);
    test_that(strcmp((char *)subitem->value.string, "def") == 0);
  }
  json_release_item(&item);

  parse_to_item("{ \"str\" : \"ing\" , \"arr\":[\"a\", []]}");
  test_that(item.type == item_object);
  test_that(item.value.object->count == 2);
  test_that(map__get(item.value.object, "str") != NULL);
  test_that(map__get(item.value.object, "arr") != NULL);
  test_that(map__get(item.value.object, "not-a-key") == NULL);

  subitem = (json_Item *)(map__get(item.value.object, "str")->value);
  test_that(subitem->type == item_string);
  test_that(strcmp(subitem->value.string, "ing") == 0);
  json_release_item(&item);

  parse_to_item("{}");
  test_that(item.type == item_object);
  json_release_item(&item);


  char *error_strings[] = {
    "{", "{, }", "{1: 2}", "{\"a\":}", "{\"b\": 34 \"c\": 35}", "{\"a\" : 1,}", "{\"a\"}"
  };
  for (int i = 0; i < array_size(error_strings); ++i) {
    parse_to_item(error_strings[i]);
    test_that(item.type == item_error);
    json_release_item(&item);
  }

  test_that(cjson_net_obj_allocs == 0);

  return test_success;
}
