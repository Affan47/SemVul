FindConstant(const char* F) const
{
    if(data->Constants.size())
    {
        unsigned ind = 0;
        while(isalnum(F[ind]) || F[ind] == '_') ++ind;
        if(ind)
        {
            string name(F, ind);
            return data->Constants.find(name);
        }
    }
    return data->Constants.end();
}
