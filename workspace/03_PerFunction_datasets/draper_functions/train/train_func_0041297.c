build_srl_tag_name(const vector<string>& tagnames, const string& frame,int startR, int endR){
		string tag = "";
		string prefix = "#";
		switch(initial_flag_){
		case EITPredArgCombination:
			prefix = "#"+ frame + "/";
		case EITArgumentCombination:
			for(int i = startR; i<=endR; i++){
				string vname;
				if(tagnames[i]=="TARGET")
					continue;
				if(tagnames[i].length() > 3)
					vname = tagnames[i].substr(3, tagnames[i].length()-3);
				else
					vname = tagnames[i];
				tag += vname;
				if(i <= endR){
					tag += "_";
				}
			}
			return prefix + tag;
		case EITGeneralX:
			return "X";
		default:
			cerr << "Error you should not go here";
			exit(1);
		}
		return "";
	}
