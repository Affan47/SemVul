subs(const map_basic_basic &subs_dict) const
{
    RCP<const Pow> self = rcp_const_cast<Pow>(rcp(this));
    auto it = subs_dict.find(self);
    if (it != subs_dict.end())
        return it->second;
    RCP<const Basic> base_new = base_->subs(subs_dict);
    RCP<const Basic> exp_new = exp_->subs(subs_dict);
    if (base_new == base_ && exp_new == exp_)
        return self;
    else
        return pow(base_new, exp_new);
}
