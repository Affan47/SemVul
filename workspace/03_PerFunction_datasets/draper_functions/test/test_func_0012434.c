Function(const vector<string>& args){
	if(!AssertArgument(args, 2, 2)) return ("");
	if (initialized){
		GetLogger().GetStream(LOG_ERROR) << "SecurityLevel is already fixed." << endl;
		return ("");
	}

	unsigned int lv=2;
	if (IsInteger(args[1])){
		lv=(unsigned int)atoi(args[1].c_str());
	}else if(args[1]=="low"){
		lv=0;
	}else if(args[1]=="middle"){
		lv=1;
	}else if(args[1]=="high"){
		lv=2;
	}else if(args[1]=="ultrahigh"){
		lv=3;
	}
	Engine->PushStrAfterClear("System.SecurityLevel", IntToString(lv));
	Engine->WriteProtect("System.SecurityLevel");
	initialized=true;
	if (GetLogger().Check(LOG_INFO)){
		switch (lv){
		case 0:
			GetLogger().GetStream() << "SecurityLevel: low" << endl; break;
		case 1:
			GetLogger().GetStream() << "SecurityLevel: middle" << endl; break;
		case 2:
			GetLogger().GetStream() << "SecurityLevel: high" << endl; break;
		case 3:
			GetLogger().GetStream() << "SecurityLevel: ultrahigh" << endl; break;
		}
	}
	return ("");
}
