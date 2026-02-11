subs(const map_basic_basic &subs_dict) const
{
    auto it = subs_dict.find(rcp(this));
    if (it != subs_dict.end())
        return it->second;
    RCP<const Basic> arg = arg_->subs(subs_dict);
    if (arg == arg_)
        return rcp(this);
    else
        return this->create(arg);
}
