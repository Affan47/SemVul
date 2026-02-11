_readWord()
{
	int i = 0;

    for(i = 0; i <= maxWordLength(); ++i)
    {
        int c = fgetc(d_file_ptr);

        if (ferror(d_file_ptr) || feof(d_file_ptr))
            throw AiksaurusException(AiksaurusException::CORRUPT_WORDS_FILE);

        if (!c) {
            d_word[i] = 0;
            break;
        }

        else
            d_word[i] = c;
    }


    for(i = 0; ;++i)
    {
        int x1 = fgetc(d_file_ptr),
            x2 = fgetc(d_file_ptr);

        if (ferror(d_file_ptr) || feof(d_file_ptr))
            throw AiksaurusException(AiksaurusException::CORRUPT_WORDS_FILE);

        if ((x1 == 0xFF) && (x2 == 0xFF))
        {
            d_links[i] = -1;
            break;
        }

        else if (i > s_maxLinks)
            throw AiksaurusException(AiksaurusException::CORRUPT_WORDS_FILE);

        d_links[i] = (x1 << 8) | x2;
    }
}
