count(object_cref sub, object_cref start, object_cref end) const
{
    return extract<long>(this->attr("count")(sub,start,end));
}
