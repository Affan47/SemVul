set_json_value(Json *json, Value *value){
	VHash *top = json->stack.top_value();
	if(json->key == NULL){
		top->hash().put(String(format(top->get_hash()->count(), 0)), value);
	} else {
		switch (json->distinct){
			case Json::D_EXCEPTION:
				if (top->hash().put_dont_replace(*json->key, value))
					throw Exception(PARSER_RUNTIME, json->key, "duplicate key");
				break;
			case Json::D_FIRST:
				top->hash().put_dont_replace(*json->key, value);
				break;
			case Json::D_LAST:
				top->hash().put(*json->key, value);
				break;
			case Json::D_ALL:
				if (top->hash().put_dont_replace(*json->key, value)){
					for(int i=2;;i++){
						String key;
						key << *json->key << "_" << format(i, 0);
						if (!top->hash().put_dont_replace(key, value)) break;
					}
				}
				break;
		}
		json->key=NULL;
	}
}
