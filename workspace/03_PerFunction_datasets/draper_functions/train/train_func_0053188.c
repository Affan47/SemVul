operator= ( const KDataToolInfo& info )
{
    d->service = info.service();
    d->componentData = info.componentData();
    return *this;
}
