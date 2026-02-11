pushCharStream  (pANTLR3_LEXER lexer,  pANTLR3_INPUT_STREAM input)
{


	if	(lexer->rec->state->streams == NULL)
	{


		lexer->rec->state->streams = antlr3StackNew(0);

		if  (lexer->rec->state->streams == NULL)
		{


			return;
		}
	}


	lexer->input->istream->mark(lexer->input->istream);
	lexer->rec->state->streams->push(lexer->rec->state->streams, lexer->input, NULL);


	lexer->setCharStream(lexer, input);
}
