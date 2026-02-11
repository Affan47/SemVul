dispatch(UDPService *obj, void*)
{
    object_name = QString::fromUtf8(obj->getName().c_str());
    type_name = obj->getTypeName().c_str();
    src_port_range_start = obj->getSrcRangeStart();
    src_port_range_end = obj->getSrcRangeEnd();
    dst_port_range_start = obj->getDstRangeStart();
    dst_port_range_end = obj->getDstRangeEnd();
    return this;
}
