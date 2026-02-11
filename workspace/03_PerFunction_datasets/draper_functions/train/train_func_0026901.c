main(int , char **)
{
	char dummy;
	topOfStack = &dummy;


	CTinyJS *js = new CTinyJS();


	js->addNative("function print(text)", &js_print, 0);


	js->setStackBase(topOfStack-(sizeOfStack-sizeOfSafeStack));
	try {
		js->execute("var lets_quit = 0; function quit() { lets_quit = 1; }");
		js->execute("print(\"Interactive mode... Type quit(); to exit, or print(...); to print something, or dump() to dump the symbol table!\");");
		js->execute("print(function () {print(\"gen\");yield 5;yield 6;}().next());", "yield-test.js");
		js->execute("for each(i in function () {print(\"gen\");yield 5;yield 6;}()) print(i);", "yield-test.js");
		js->execute("function g(){				\n\n"
			"	throw \"error\"\n"
			"	try{									\n"
			"		yield 1; yield 2				\n"
			"	}finally{							\n"
			"		print(\"finally\")			\n"
			"		yield 3;							\n"
			"		throw StopIteration			\n"
			"	}										\n"
			"	print(\"after finally\")		\n"
			"}t=g()", "test");
	} catch (CScriptException *e) {
		printf("%s\n", e->toString().c_str());
		delete e;
	}
	int lineNumber = 0;
	while (js->evaluate("lets_quit") == "0") {
		std::string buffer;
		if(!std::getline(std::cin, buffer)) break;
		try {
			js->execute(buffer, "console.input", lineNumber++);
		} catch (CScriptException *e) {
			printf("%s\n", e->toString().c_str());
			delete e;
		}
	}
	delete js;
#ifdef _WIN32
#ifdef _DEBUG


	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
#endif
	return 0;
}
