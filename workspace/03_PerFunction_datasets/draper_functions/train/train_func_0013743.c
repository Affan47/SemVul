operator=(const TDUID &duid) {
    if (this==&duid)
        return *this;

    if(this->DUID)
        delete this->DUID;

    this->DUID=new char [duid.len];
    memcpy(this->DUID,duid.DUID,duid.len);
    this->len=duid.len;
    this->Plain=duid.Plain;

    return *this;
}
