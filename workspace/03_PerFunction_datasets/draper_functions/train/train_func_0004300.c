substr(unsigned s, unsigned l) const {
#ifdef KYTEA_SAFE
    if(s+l > length())
        throw runtime_error("substr out of bounds");
#endif
    KyteaString ret(l);
    memcpy(ret.getImpl()->chars_, impl_->chars_+s, sizeof(KyteaChar)*l);
    return ret;
}
