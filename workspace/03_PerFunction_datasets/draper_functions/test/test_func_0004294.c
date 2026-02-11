executionPaths()
{

    {

        if (_settings->_jobs == 1)
            UninitVar::analyseFunctions(_tokenizer->tokens(), UninitVar::uvarFunctions);

        UninitVar c(this);
        checkExecutionPaths(_tokenizer->tokens(), &c);
    }
}
