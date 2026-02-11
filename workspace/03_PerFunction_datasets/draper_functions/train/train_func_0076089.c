main()
{
	setlocale(LC_ALL, "");

	string json_text = "{ \"some_text\": \"Test... \\u00a320\" }";

	json::Value *v;
	json::Object *obj;

	v = json::parse(json_text);
	obj = dynamic_cast<json::Object *>(v);
	print_object(*obj);

	stringstream ss;
	json::generate(*obj, ss);
	cout << ss.str() << endl;
}
