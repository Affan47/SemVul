phrase(int output)
{
      List *wordList = 0;
      double weight = 1.0;

      while (1)
	{
	  if (match('"'))
	    {
	      if (output)
	      {
                if(!wordList) wordList = new List;
		if(debug) cerr << "scoring phrase" << endl;
		score(wordList, weight, FLAGS_MATCH_ONE);
	      }
	      break;
	    }
	  else if (lookahead == WORD)
	    {
	      weight *= current->weight;
	      if (output)
		perform_phrase(wordList);

	      lookahead = lexan();
	    }
          else if (lookahead == DONE)
           {
	     setError(boolean_syntax_errors[QUOTE]);
	     break;
           }
	  else
	   {

	     current->isIgnore = 1;
	     if (output)
		perform_phrase(wordList);
	     lookahead = lexan ();
	   }
	}
	if(wordList) delete wordList;
}
