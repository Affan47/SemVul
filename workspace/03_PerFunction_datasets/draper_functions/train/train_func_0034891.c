__hash__() const
{
    std::size_t seed = FUNCTIONSYMBOL;
    for (auto &a : arg_)
        hash_combine<Basic>(seed, *a);
    hash_combine<std::string>(seed, name_);
    return seed;
}
