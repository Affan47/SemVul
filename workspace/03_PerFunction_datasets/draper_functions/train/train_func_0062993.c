executionPaths()
{

    {

        if (_settings->_jobs == 1)
            UninitVar::analyseFunctions(_tokenizer->tokens(), UninitVar::uvarFunctions);

        UninitVar c(this, _tokenizer->getSymbolDatabase(), &_settings->library, _tokenizer->isC());
        checkExecutionPaths(_tokenizer->getSymbolDatabase(), &c);
    }
}
