leakError(const Token *tok, const std::string &varname, int type)
{
    const CheckMemoryLeak checkmemleak(_tokenizer, _errorLogger, _settings);
    if (_settings->library.isresource(type))
        checkmemleak.resourceLeakError(tok, varname);
    else
        checkmemleak.memleakError(tok, varname);
}
