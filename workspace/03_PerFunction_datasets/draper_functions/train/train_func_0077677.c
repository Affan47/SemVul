seekAndParseSpecificParamTag(nor_utils::StreamTokenizer& st, const string& tag, const string& targetTagParam, string& paramValue)
	{
		bool tagFound = false;
		string rawTag;
		string foundTag;
		string::const_iterator p;

        string tagParam;

		tagParam = "";
		paramValue = "";

		do {


			rawTag = st.next_token();
			foundTag = "";

			p = rawTag.begin();


			insert_iterator<string> tagIt(foundTag, foundTag.begin());
			for ( ; p != rawTag.end(); ++p)
			{
				if ( isspace(*p) )
					break;
				*tagIt = *p;
			}

			if ( nor_utils::cmp_nocase(tag, foundTag) )
			{
				tagFound = true;
				break;
			}

		} while( st.has_token() );

		if ( !tagFound )
			return false;

        while (targetTagParam.compare(tagParam) != 0 && p != rawTag.end()) {


            for ( ; isspace(*p) && p != rawTag.end() ; ++p );


            insert_iterator<string> paramIt(tagParam, tagParam.begin());
            for ( ; p != rawTag.end(); ++p)
            {
                if (*p == '=')
                    break;
                *paramIt = *p;
            }


            for ( ; p != rawTag.end() && isspace(*p); ++p );

            for ( ; p != rawTag.end() && *p == '='; ++p );

            for ( ; p != rawTag.end() && isspace(*p); ++p );


            for ( ; p != rawTag.end() && *p == '"'; ++p );


            insert_iterator<string> valueIt(paramValue, paramValue.begin());
            for ( ; p != rawTag.end(); ++p)
            {
                if (*p == '\"')
                    break;
                *valueIt = *p;
            }

        }

		return true;
	}
