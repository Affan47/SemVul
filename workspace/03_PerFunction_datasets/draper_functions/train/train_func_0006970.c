SerializeUncovered_PhraseOnly(const string& source, const string& target){
		string src = source + " ||| " + target + " ||| 0-0 ";
		string tgt = target + " ||| " + source + " ||| 0-0 ";
		return pair<string,string>(src,tgt);
	}
