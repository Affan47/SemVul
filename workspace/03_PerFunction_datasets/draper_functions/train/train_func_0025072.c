getHash() const {
    size_t hash = 5381;
    if(impl_==0)
        return hash;
    const unsigned l = impl_->length_;
    const KyteaChar* cs = impl_->chars_;
    for(unsigned i = 0; i < l; i++)
        hash = ((hash << 5) + hash) + cs[i];
    return hash;
}
