isUnsigned(const Variable* var) const
{
    return(var && var->typeStartToken()->isUnsigned() && !var->isPointer() && !var->isArray() && _tokenizer->sizeOfType(var->typeStartToken()) >= _settings->sizeof_int);
}
