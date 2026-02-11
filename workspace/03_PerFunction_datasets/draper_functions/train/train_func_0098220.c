eb_set_endword(EB_Book *book, const char *input_word, char *word,
    char *canonicalized_word, EB_Word_Code *word_code)
{
    EB_Error_Code error_code;
    const EB_Search *search;

    LOG(("in: eb_set_endword(book=%d, input_word=%s)", (int)book->code,
	eb_quoted_string(input_word)));


    if (book->character_code == EB_CHARCODE_ISO8859_1)
	error_code = eb_convert_latin(book, input_word, word, word_code);
    else
	error_code = eb_convert_euc_jp(book, input_word, word, word_code);
    if (error_code != EB_SUCCESS)
	goto failed;
    strcpy(canonicalized_word, word);


    switch (*word_code) {
    case EB_WORD_ALPHABET:
	if (book->subbook_current->endword_alphabet.start_page != 0)
	    search = &book->subbook_current->endword_alphabet;
	else if (book->subbook_current->endword_asis.start_page != 0)
	    search = &book->subbook_current->endword_asis;
	else {
	    error_code = EB_ERR_NO_SUCH_SEARCH;
	    goto failed;
	}
	break;

    case EB_WORD_KANA:
	if (book->subbook_current->endword_kana.start_page != 0)
	    search = &book->subbook_current->endword_kana;
	else if (book->subbook_current->endword_asis.start_page != 0)
	    search = &book->subbook_current->endword_asis;
	else {
	    error_code = EB_ERR_NO_SUCH_SEARCH;
	    goto failed;
	}
	break;

    case EB_WORD_OTHER:
	if (book->subbook_current->endword_asis.start_page != 0)
	    search = &book->subbook_current->endword_asis;
	else {
	    error_code = EB_ERR_NO_SUCH_SEARCH;
	    goto failed;
	}
	break;

    default:
	error_code = EB_ERR_NO_SUCH_SEARCH;
	goto failed;
    }


    eb_fix_word(book, search, word, canonicalized_word);


    if (book->character_code == EB_CHARCODE_ISO8859_1) {
	eb_reverse_word_latin(word);
	eb_reverse_word_latin(canonicalized_word);
    } else {
	eb_reverse_word_jis(word);
	eb_reverse_word_jis(canonicalized_word);
    }

    LOG(("out: eb_set_endword(word=%s, canonicalized_word=%s, word_code=%d) \
= %s",
	eb_quoted_string(word), eb_quoted_string(canonicalized_word),
	(int)*word_code, eb_error_string(EB_SUCCESS)));

    return EB_SUCCESS;


  failed:
    *word = '\0';
    *canonicalized_word = '\0';
    *word_code = EB_WORD_INVALID;
    LOG(("out: eb_set_endword() = %s", eb_error_string(error_code)));
    return error_code;
}
